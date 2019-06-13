#pragma once

#include "Abstract_WorldmapController.h"	//WC

//Converts sensor data into data for WC and returns worldmap data for navigation purposes

class Abstract_WorldTranslator {	//WT
public:
	Abstract_WorldTranslator() {};
	virtual void updateWorldmap(double *sensorData, double currentRotation) = 0;	//turns sensor data into a 2D array for the world map
	virtual double* getSurroundings() = 0;	//returns data from the worldmap in a convenient format for circumnavigation
protected:
	Abstract_WorldmapController * worldmapController;
};