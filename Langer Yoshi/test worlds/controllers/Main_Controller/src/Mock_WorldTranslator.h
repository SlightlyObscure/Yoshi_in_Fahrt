#pragma once

#include "Abstract_WorldTranslator.h"

class Mock_WorldTranslator : public Abstract_WorldTranslator {
public:
	Mock_WorldTranslator();
	void updateWorldmap(double *sensorData);
	double* getSurroundings();
};