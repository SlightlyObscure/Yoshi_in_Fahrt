#pragma once

#include "Worldmap.h"
#include "Mapdata.h"

class Abstract_WorldmapController {		//WC
public:
	Abstract_WorldmapController() {};
	virtual void update(Mapdata newData) = 0;
	virtual Mapdata getSurroundings() = 0;
protected:
	Worldmap worldmap;
};