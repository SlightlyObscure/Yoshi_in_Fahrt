#include "stdafx.h"

#include "Mock_WorldTranslator.h"
#include "Mock_WorldmapController.h"

//NOTE: This is a mock implementation that needs to be replaced once a proper worldmap is to be implemented

Mock_WorldTranslator::Mock_WorldTranslator() {
	this->worldmapController = new Mock_WorldmapController();
}

void Mock_WorldTranslator::updateWorldmap(double * sensorData, double currentRotation) {
	//sensorData should be converted into 2D array
	//currentRotation sould be used to "rotate" sensorData so that the worldmap is filled correctly  

	Mapdata md;
	for (int i = 0; i < MAX_SENSOR_NUMBER; i++) {
		md.mockData[i] = *(sensorData + i);
	}
	
	worldmapController->update(md);
}

double * Mock_WorldTranslator::getSurroundings() {
	//this should return data from the worldmap in a convenient format for circumnavigation

	double *data = worldmapController->getSurroundings().mockData;
	double *ret = new double[16];
	for (int i = 0; i < 16; i++) {
		ret[i] = *(data + i);
	}
	return ret;
}
