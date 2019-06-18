#pragma once

#include "Abstract_Motors.h"

#define MOVEMENT_SPEED 5.0
#define ROT_MULT_MOD 1.7
#define ROT_ADD_MOD 0.0 

class P3AT_Motors : public Abstract_Motors {	//see Abstract_Motors.h for more information
public:
	P3AT_Motors(std::vector<WbDeviceTag> motors, double radius_wheel, double rotation_speed, double umfang_wendekreis);
	void rotate(double degree);
	void drive(double distance);
	void stop(void);
	bool isDone(bool isTurning, double distance, double degree);
	double getDonePercentage(bool isTurning, double distance, double degree);

private:
	void setLeftWheelsSpeed(double speed);
	void setRightWheelsSpeed(double speed);
	void setAllWheelsSpeed(double speed);
	void recalcDistance(bool isTurning);	//updates distance driven between last check and this check
	double RpsToMps(double rps, double radius); //converts radiant per second to meters per second
	double degreeToDistance(double rotationDegree);	//converts degrees into driving distance so that an aproximate completion time can be calculated

	double _distanceDriven = 0;
	double _startTimeStamp;
	double _calculatedDuration;
};