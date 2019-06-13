#pragma once

#include "Abstract_WorldmapController.h"

//NOTE: This is a mock implementation that needs to be replaced once a proper worldmap is to be implemented

class Mock_WorldmapController : public Abstract_WorldmapController {
public:
	Mock_WorldmapController();
	void update(Mapdata newData);
	Mapdata getSurroundings();
};