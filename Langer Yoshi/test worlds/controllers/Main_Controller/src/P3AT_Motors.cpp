#include "stdafx.h"

#include "P3AT_Motors.h"
#include "Log.h"

P3AT_Motors::P3AT_Motors(std::vector<WbDeviceTag> motors, double radius_wheel, double rotation_speed, double umfang_wendekreis)
	: Abstract_Motors(motors, radius_wheel, rotation_speed, umfang_wendekreis) {
	this->RADIUS_WHEEL = radius_wheel;
	this->ROTATION_SPEED = 5;
	this->UMFANG_WENDEKREIS = umfang_wendekreis;
	this->_motors = motors;

	for (auto motor : _motors) {
		wb_motor_set_position(motor, INFINITY);	//this is required for webots to function correctly
	}
}

void P3AT_Motors::setLeftWheelsSpeed(double speed) {
    wb_motor_set_velocity(wb_robot_get_device("front left wheel"), speed);
    return;

	if (this->_motors.size() == 2) {
		wb_motor_set_velocity(this->_motors[0], speed);
	}
	else if (this->_motors.size() == 4) {
		wb_motor_set_velocity(this->_motors[0], speed);
		wb_motor_set_velocity(this->_motors[1], speed);
	}
}
void P3AT_Motors::setRightWheelsSpeed(double speed) {
    wb_motor_set_velocity(wb_robot_get_device("front right wheel"), speed);
    return;

    if (this->_motors.size() == 2) {
		wb_motor_set_velocity(this->_motors[1], speed);
	}
	else	if (this->_motors.size() == 4) {
		wb_motor_set_velocity(this->_motors[2], speed);
		wb_motor_set_velocity(this->_motors[3], speed);
	}
}

void P3AT_Motors::setAllWheelsSpeed(double speed) {
    wb_motor_set_velocity(wb_robot_get_device("front right wheel"), speed);
    wb_motor_set_velocity(wb_robot_get_device("front left wheel"), speed);
    
    return;
	for (auto motor : _motors) {
		wb_motor_set_velocity(motor, speed);
	}
}

void P3AT_Motors::rotate(double degree) {
	int direction;
	direction = degree > 0 ? 1 : -1;	//if degree is positive -> turn right; else turn left

	this->_distanceDriven = 0;
	this->_startTimeStamp = wb_robot_get_time();	//record current time
	
	//set speed of left and right motors in opposite directions
	if(degree > 0) {
        this->setRightWheelsSpeed(MOVEMENT_SPEED);
        this->setLeftWheelsSpeed(0);
	}
	else {
        this->setLeftWheelsSpeed(MOVEMENT_SPEED);
        this->setRightWheelsSpeed(0);
	}


}
void P3AT_Motors::drive(double distance) {
	this->_distanceDriven = 0;
	this->_startTimeStamp = wb_robot_get_time();	//record current time

	//if distance is positive set motors to drive forwards; else set motors to drive backwards
	if (distance > 0) {
		this->setAllWheelsSpeed(MOVEMENT_SPEED);
	}
	else {
		this->setAllWheelsSpeed(-MOVEMENT_SPEED);
	}
}

void P3AT_Motors::recalcDistance(bool isTurning) {
	//calc time since last update and record current time again
	double intermediateTime = wb_robot_get_time() - this->_startTimeStamp;
	this->_startTimeStamp = wb_robot_get_time();

	//calculate distance driven since last update using current speed and intermediate time
	if (isTurning) {
		double currentSpeed = RpsToMps(wb_motor_get_velocity(this->_motors[0]), this->RADIUS_WHEEL) * (0.390 / 0.473);	//komplizierte Formel f�r dreh geschwindigkeit :O
		this->_distanceDriven += currentSpeed * intermediateTime;
	}
	else {
		this->_distanceDriven += (RpsToMps(wb_motor_get_velocity(this->_motors[0]), this->RADIUS_WHEEL) * intermediateTime);
	}

}

bool P3AT_Motors::isDone(bool isTurning, double distance, double degree) {
	recalcDistance(isTurning);	//update _distanceDriven

	//check if turning or driving part of command is done
	if (isTurning) {
		if (abs(degreeToDistance(degree)) - 0.01 < abs(this->_distanceDriven)) {
			this->setAllWheelsSpeed(0);
			return true;
		}
	}
	else {
		if (abs(distance) - 0.01 < abs(this->_distanceDriven)) {
			this->setAllWheelsSpeed(0);
			return true;
		}
	}
	return false;
}

double P3AT_Motors::getDonePercentage(bool isTurning, double distance, double degree) {
	double commandDist;

	//get total distance of current command
	if (isTurning) {
		commandDist = abs(degreeToDistance(degree));
	}
	else {
		commandDist = abs(distance);
	}

	return abs(this->_distanceDriven) / commandDist;	//divide distance that has already been driven by total distance that needs to be driven for the command to be completed
}

void P3AT_Motors::stop(void) {
	this->setAllWheelsSpeed(0);
}

/*
*Radiant per Second to Meters per Second Converter
*Given: Speed in radiant per seconds and radius of the wheel
*Requirements: Radius has to be given in meter
*Return: Speed in meters per second
*/
double P3AT_Motors::RpsToMps(double rps, double radius) {
	return rps * radius;
}

double P3AT_Motors::degreeToDistance(double rotationDegree) {
	return (rotationDegree / 360.0) * this->UMFANG_WENDEKREIS;
}
