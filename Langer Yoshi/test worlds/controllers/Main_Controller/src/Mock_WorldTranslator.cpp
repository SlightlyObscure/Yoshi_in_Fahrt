#include "stdafx.h"

#include "Mock_WorldTranslator.h"
#include "Mock_WorldmapController.h"

Mock_WorldTranslator::Mock_WorldTranslator() {
	this->worldmapController = new Mock_WorldmapController();
}

void Mock_WorldTranslator::updateWorldmap(double * sensorData) {
	Mapdata md;
	for (int i = 0; i < MAX_SENSOR_NUMBER; i++) {
		md.mockData[i] = *(sensorData + i);
	}
	
	worldmapController->update(md);
}

double * Mock_WorldTranslator::getSurroundings() {
	double *data = worldmapController->getSurroundings().mockData;
	double *ret = new double[16];
	for (int i = 0; i < 16; i++) {
		ret[i] = *(data + i);
	}
	return ret;
}
