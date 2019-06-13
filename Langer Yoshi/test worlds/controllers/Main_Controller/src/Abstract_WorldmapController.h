#pragma once

#include "Worldmap.h"
#include "Mapdata.h"

//This class updates the worldmap and can return the portion of the worldmap surrounding the robot

class Abstract_WorldmapController {		//WC
public:
	Abstract_WorldmapController() {};
	virtual void update(Mapdata newData) = 0;	//adds newData to the worldmap around the robot's current position
	virtual Mapdata getSurroundings() = 0;		//returns worldmap around robot
protected:
	Worldmap worldmap;
};