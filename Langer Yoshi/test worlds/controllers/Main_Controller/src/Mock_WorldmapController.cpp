#include "stdafx.h"

#include "Mock_WorldmapController.h"

Mock_WorldmapController::Mock_WorldmapController() {
}

void Mock_WorldmapController::update(Mapdata newData) {
	worldmap.mockMap = newData;
}

Mapdata Mock_WorldmapController::getSurroundings() {
	return worldmap.mockMap;
}
