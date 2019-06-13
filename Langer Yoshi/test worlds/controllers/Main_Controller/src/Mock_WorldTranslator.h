#pragma once

#include "Abstract_WorldTranslator.h"

//NOTE: This is a mock implementation that needs to be replaced once a proper worldmap is to be implemented

class Mock_WorldTranslator : public Abstract_WorldTranslator {
public:
	Mock_WorldTranslator();
	void updateWorldmap(double *sensorData, double currentRotation);
	double* getSurroundings();
};