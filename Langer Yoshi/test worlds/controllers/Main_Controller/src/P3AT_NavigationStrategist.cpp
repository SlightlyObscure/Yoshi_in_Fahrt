#include "stdafx.h"

#include "P3AT_NavigationStrategist.h"
#include "Log.h"

P3AT_NavigationStrategist::P3AT_NavigationStrategist(Abstract_RoadmapController *rc, Abstract_CommandHandler *ch, Abstract_WorldTranslator *wt)
	: Abstract_NavigationStrategist::Abstract_NavigationStrategist(rc, ch, wt){
	this->worldTranslator = wt;
	this->roadmapController = rc;
	//add pointer of NS to CH and of CH to NS (2-ways communication)
	this->commandHandler = ch;
	this->commandHandler->addNavigationStrategist(this);
	//set current position to (0, 0)
	this->currentPosition.x = 0;
	this->currentPosition.y = 0;
}

void P3AT_NavigationStrategist::mcDone(double rotation) {
	if (noOldWayPoint == true) {	//if there is no old way point to discard skip the discarding step
		noOldWayPoint = false;
	}
	else {	
		//update position with last destination and then discard it
		WayPoint newPos = roadmapController->getCoord();
		currentPosition = newPos;
		roadmapController->delCoord();

		//update position with parsed value
		currentRotation += rotation;
	}
	
	causeMotion();
}

void P3AT_NavigationStrategist::mcDone(double rotation, double percentDone) {
	//We assume that the stop occured during the driving step because the robot doesn't usually stop while turning
	currentRotation += rotation;
	//Get original destination to calculate a vector
	WayPoint dest = roadmapController->getCoord();
	//calculate vector and multiply with the completion percentage of the command
	double vecX = (dest.x - currentPosition.x) * percentDone;
	double vecY = (dest.y - currentPosition.y) * percentDone;
	
	//add vector to starting position to get new current position
	currentPosition.x += vecX;
	currentPosition.y += vecY;

	//find direction to drive where path is unoccupied
	double *sensData = worldTranslator->getSurroundings();
	double direct = getUnoccupied(sensData);
	delete[]sensData;
	
	WayPoint altRoute = getAltRoute(direct, 1);

	roadmapController->addCoord(altRoute.x, altRoute.y);

	std::ostringstream strs2;
	strs2 << "percentDone " << percentDone << "\n";
	strs2 << "posX " << currentPosition.x << ", posY: " << currentPosition.y << "\n";
	strs2 << "x: " << altRoute.x << ", y: " << altRoute.y;
	std::string str = strs2.str();
	Log::writeLog(str);
	
	causeMotion();
}

WayPoint P3AT_NavigationStrategist::getAltRoute(double direct, double driveDist) {
	double newRot = currentRotation + direct;
	if (newRot >= 360) {
		newRot -= 360;
	}
	else if (newRot < 0) {
		newRot += 360;
	}

	double vecX, vecY;

	if (newRot == 0) {
		vecX = 0;
		vecY = 1;
	}
	else if (newRot == 90) {
		vecX = 1;
		vecY = 0;
	}
	else if (newRot == 180) {
		vecX = 0;
		vecY = -1;
	}
	else if (newRot == 270) {
		vecX = -1;
		vecY = 0;
	}
	else {
		double ratio = tan(newRot * PI / 180);

		if (newRot < 180) {
			vecX = 1;
		}
		else {
			vecX = -1;
		}

		vecY = vecX / ratio;
	}
	
	double len = getVecLen(vecX, vecY);
	double scaledX = vecX / len * driveDist;
	double scaledY = vecY / len * driveDist;

	WayPoint newRoute;
	newRoute.x = currentPosition.x + scaledX;
	newRoute.y = currentPosition.y + scaledY;
	return newRoute;
}

double P3AT_NavigationStrategist::getVecLen(double vecX, double vecY) {
	double squares = (vecX * vecX) + (vecY * vecY);
	return sqrt(squares);
}

double P3AT_NavigationStrategist::getUnoccupied(double *sensData) {
	double unOcThresh = 800;
	bool front[MAX_SENSOR_NUMBER / 2] = { false };
	bool back[MAX_SENSOR_NUMBER / 2] = { false };
	for (int i = 0; i < MAX_SENSOR_NUMBER / 2; i++) {
		int backI = i + (MAX_SENSOR_NUMBER / 2);

		if (sensData[i] > unOcThresh) {
			front[i] = true;
		}
		if (sensData[backI] > unOcThresh) {
			back[i] = true;
		}
	}

	/*for (int i = 0; i < 8; i++) {
		std::ostringstream strs2;
		strs2 << "front " << i << ": " << front[i] << ", back " << i + 8 << ": " << back[i];
		std::string str = strs2.str();
		Log::writeLog(str);
	}*/

	int leftVal = 0, rightVal = 0;

	if (front[3]) {
		leftVal = -90;
	}
	else if (front[2]) {
		leftVal = -70;
	}
	else if (front[1]) {
		leftVal = -40;
	}
	else if (front[0]) {
		leftVal = -15;
	}

	if (leftVal == 0 && front[4]) {
		rightVal = 90;
	}
	else if (front[5]) {
		rightVal = 70;
	}
	else if (front[6]) {
		rightVal = 40;
	}
	else if (front[7]) {
		rightVal = 15;
	}

	if (leftVal != 0 && rightVal == 0) {
		return (double) leftVal;
	}
	else if (rightVal != 0 && leftVal == 0) {
		return (double) rightVal;
	}
	else if (leftVal == 0 && rightVal == 0) {
		return 0;
	}
	else {
		return -180;
	}
}



void P3AT_NavigationStrategist::causeMotion() {
	//get next destination
	WayPoint nextWP = roadmapController->getCoord();

	//if there are no destinations left set noOldWayPoint to true
	if (nextWP.isEmpty) {
		noOldWayPoint = true;
	}
	commandHandler->commandMotor(currentRotation, currentPosition, nextWP);
}

void P3AT_NavigationStrategist::stopMotors(bool inclTurning) {
	commandHandler->stop(inclTurning);
}

void P3AT_NavigationStrategist::updateWorldmap(double * sensorData) {
	worldTranslator->updateWorldmap(sensorData);
}


