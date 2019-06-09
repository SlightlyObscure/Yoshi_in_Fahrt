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
	double thresh[8] = { 950, 935, 925, 900, 900, 925, 935, 950 };
	navigationStrategist->updateWorldmap(ultraData);

	for (int i = 0; i < (MAX_SENSOR_NUMBER / 2); i++) {
		if (ultraData[i] >= thresh[i]) {
			navigationStrategist->stopMotors(false);
		}
	}

	if (bumper->getData()) {
		navigationStrategist->stopMotors(true);
	}
}