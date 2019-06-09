#pragma once

#include "Abstract_NavigationStrategist.h"

class Abstract_SensorController {
public:
	Abstract_SensorController(Abstract_NavigationStrategist *ns) { };
	virtual void checkSenses() = 0;
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