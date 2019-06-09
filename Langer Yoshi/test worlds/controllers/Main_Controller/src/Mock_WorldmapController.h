#pragma once

#include "Abstract_WorldmapController.h"

class Mock_WorldmapController : public Abstract_WorldmapController {
public:
	Mock_WorldmapController();
	void update(Mapdata newData);
	Mapdata getSurroundings();
};