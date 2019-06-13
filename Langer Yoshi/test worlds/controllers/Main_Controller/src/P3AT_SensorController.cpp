#include "stdafx.h"

#include "P3AT_SensorController.h"
#include "Log.h"

static WbDeviceTag sensors[MAX_SENSOR_NUMBER];

P3AT_SensorController::P3AT_SensorController(Abstract_NavigationStrategist *ns) : Abstract_SensorController::Abstract_SensorController(ns) {
	this->navigationStrategist = ns;

	ultrasound = new P3AT_Ultrasound();
	bumper = new P3AT_Bumper();
}

void P3AT_SensorController::checkSenses() {
	double *ultraData = ultrasound->getData();
	double thresh[8] = { 950, 935, 925, 900, 900, 925, 935, 950 };	//threshold for when robot should stop; more strict in front because stop is more likely necessary
	
	//check sensor data and stop if necessary
	for (int i = 0; i < (MAX_SENSOR_NUMBER / 2); i++) {
		if (ultraData[i] >= thresh[i]) {	
			navigationStrategist->stopMotors(false);	//inclTurning false because robot doesn't need to stop if it's turning
		}
	}

	if (bumper->getData()) {
		navigationStrategist->stopMotors(true);		//inclTurning true because getting true from bumper indicates a dangerous situation
	}

	navigationStrategist->updateWorldmap(ultraData);	//send sensor data off to be recorded in worldmap
}