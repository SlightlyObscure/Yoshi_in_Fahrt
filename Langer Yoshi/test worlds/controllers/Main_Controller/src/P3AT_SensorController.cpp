#include "stdafx.h"

#include "P3AT_SensorController.h"
#include "Log.h"

static WbDeviceTag sensors[16];

P3AT_SensorController::P3AT_SensorController(Abstract_NavigationStrategist *ns) : Abstract_SensorController::Abstract_SensorController(ns) {
	this->navigationStrategist = ns;

	ultrasound = new P3AT_Ultrasound();
	bumper = new P3AT_Bumper();
}

void P3AT_SensorController::checkSenses() {
	double *ultraData = ultrasound->getData();
	double thresh[8] = { 950, 850, 825, 800, 800, 825, 850, 950 };	//threshold for when robot should stop; more strict in front because stop is more likely necessary
	
	//check sensor data and stop if necessary
	for (int i = 0; i < 8; i++) {
		if (ultraData[i] >= thresh[i]) {
			navigationStrategist->stopMotors(false);	//inclTurning false because robot doesn't need to stop if it's turning
            /*std::ostringstream strs;
            strs << i << " sensor: " << ultraData[i];

            std::string str = strs.str();*/
			//Log::writeLog("hallo?");
		}
	}

	if (bumper->getData()) {
		//navigationStrategist->stopMotors(true);		//inclTurning true because getting true from bumper indicates a dangerous situation
	}

	navigationStrategist->updateWorldmap(ultraData);	//send sensor data off to be recorded in

	delete[]ultraData;
}