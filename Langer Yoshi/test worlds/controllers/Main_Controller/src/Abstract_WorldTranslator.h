#pragma once

#include "Abstract_WorldmapController.h"

class Abstract_WorldTranslator {	//WT
public:
	Abstract_WorldTranslator() {};
	virtual void updateWorldmap(double *sensorData) = 0;
	virtual double* getSurroundings() = 0;
protected:
	Abstract_WorldmapController * worldmapController;
};