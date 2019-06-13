#pragma once

#include "Abstract_NavigationStrategist.h"	//NS

//This class holds the robot's sensors and acts as an abstraction layer. It also makes the robot stop if sensor data indicates an obstacle immediately in front of the robot

class Abstract_SensorController {
public:
	Abstract_SensorController(Abstract_NavigationStrategist *ns) { };
	virtual void checkSenses() = 0; // is called in main loop to check for and forward sensor data; also calls stopMotors in NS if robot should stop because of obstacles
protected:
	Abstract_NavigationStrategist * navigationStrategist;
};


/*
Sensor indexes:#
0-7: Front
0: -90° to front; leftmost
1: -64,3° to front
2: -38,6° to front
3: -12,9° to front; front-ish
4: 12,9° to front; front-ish
5: 38,6° to front
6: 64,3° to front
7: 90° to front; rightmost
8-16: Back
*/