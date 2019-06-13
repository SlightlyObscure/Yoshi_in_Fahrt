#include "stdafx.h"

#include "Mock_WorldmapController.h"

//NOTE: This is a mock implementation that needs to be replaced once a proper worldmap is to be implemented

Mock_WorldmapController::Mock_WorldmapController() {
}

void Mock_WorldmapController::update(Mapdata newData) {
	//this should use a parsed 2D array and add its values to the worldmap 
	//from ( currentPosX - (newData.width / 2) ) to ( currentPosX + (newData.width / 2) )
	//and ( currentPosY - (newData.height / 2) ) to ( currentPosY + (newData.height / 2) )

	worldmap.mockMap = newData;
}

Mapdata Mock_WorldmapController::getSurroundings() {
	//this should return the portion of the worldmap the robot is currently in as Mapdata

	return worldmap.mockMap;
}
