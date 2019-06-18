#include "stdafx.h"

#include "P3AT_MotorController.h"
#include "P3AT_CommandHandler.h"
#include "Command.h"
#include "Log.h"



P3AT_MotorController::P3AT_MotorController() : Abstract_MotorController::Abstract_MotorController() {
	// get devices
	WbDeviceTag front_left_wheel = wb_robot_get_device("front left wheel");
	WbDeviceTag front_right_wheel = wb_robot_get_device("front right wheel");
	WbDeviceTag back_left_wheel = wb_robot_get_device("back left wheel");
	WbDeviceTag back_right_wheel = wb_robot_get_device("back right wheel");

	std::vector<WbDeviceTag> motVec;
	motVec.push_back(front_left_wheel);
	motVec.push_back(back_left_wheel);
	motVec.push_back(front_right_wheel);
	motVec.push_back(back_right_wheel);

	double radius_wheel = 0.10;	//Reifenradius ~10cm???
	double rotation_speed = 2 * PI; //Eine halbe Reifenumdrehung pro Sekunde
	double umfang_wendekreis = 1.6336;	//Diagonale Rad zu Rad ~ 70cm -> Kreisumfang mit der Diagonale als Ann�herung in Meter (1.6336)

	currentCommand.isObsolete = true;

	this->Motors = new P3AT_Motors(motVec, radius_wheel, rotation_speed, umfang_wendekreis);
}

void P3AT_MotorController::doCommand(Command c) {
	//set received command as new current command
	this->currentCommand = c;

	if (!currentCommand.isObsolete) {
		if (_isTurning) {
			rotate(currentCommand.rotation);
		}
		else {
			drive(currentCommand.distance);
		}
	}
}


void P3AT_MotorController::stop(bool inclTurning) {
	if (!_isTurning || inclTurning) {
		this->Motors->stop();
		this->_isStopped = true;
	}
	if (inclTurning) {	//if inclTurning is true something bad happend and robot should not start moving again
		this->_isVeryStopped = true;
	}
}


double P3AT_MotorController::getIntermediate() {
	return calcDistance(_isTurning);
}

bool P3AT_MotorController::getIsTurning() {
	return _isTurning;
}


void P3AT_MotorController::rotate(double degrees) {
	this->Motors->rotate(degrees);
}


void P3AT_MotorController::drive(double metres) {
	this->Motors->drive(metres);
}

double P3AT_MotorController::calcDistance(bool turning) {
	return Motors->getDonePercentage(turning, currentCommand.distance, currentCommand.rotation);
}

void P3AT_MotorController::check() {
	if (_isVeryStopped) {
		Log::writeLog("robot is very stopped");	//bad english = deliberate
	}
	else if (_isStopped) {
		//initiate circumnavigation strategy
		std::cout << "stopped" << std::endl;

		_isStopped = false;
		_isTurning = true;
		reportStop();
	}
	else if (currentCommand.isObsolete == true) {
		fetchNextCommand();
	}
	else if (this->Motors->isDone(_isTurning, currentCommand.distance, currentCommand.rotation)) {
		if (_isTurning) {	//if turning portion was just completed start driving portion
			_isTurning = false;
			doCommand(currentCommand);
		}
		else {	//if driving portion was just completed get next command
			_isTurning = true;
			Motors->stop();
			fetchNextCommand();
		}
	}
}

void P3AT_MotorController::fetchNextCommand() {
	commandHandler->mcDone(currentCommand.rotation);
}

void P3AT_MotorController::reportStop() {
	double percentDone = calcDistance(false);
	commandHandler->mcDone(currentCommand.rotation, percentDone);
}

void P3AT_MotorController::addCommandHandler(Abstract_CommandHandler *ch) {
	commandHandler = ch;
}