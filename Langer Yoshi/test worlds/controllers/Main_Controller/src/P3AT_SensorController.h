#pragma once

#include "P3AT_Bumper.h"
#include "P3AT_Ultrasound.h"
#include "Abstract_SensorController.h"

class P3AT_SensorController : public Abstract_SensorController {	//see Abstract_SensorController.h for more information
public:
	P3AT_SensorController(Abstract_NavigationStrategist *ns);
	void checkSenses();
private:
	P3AT_Bumper *bumper;	//bumper sensor	(outputs true if bumper was triggered)
	P3AT_Ultrasound *ultrasound;	//ultrasound array (16 total; 8 on front, 8 on back; cover 360°; outputs values within [0; 1024])
};