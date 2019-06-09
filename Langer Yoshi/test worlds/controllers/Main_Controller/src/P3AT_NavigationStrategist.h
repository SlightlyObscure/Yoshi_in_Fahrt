#pragma once

#include "Abstract_NavigationStrategist.h"
#include "P3AT_RoadmapController.h"
#include "P3AT_CommandHandler.h"
#include "Mock_WorldTranslator.h"

class P3AT_NavigationStrategist : public Abstract_NavigationStrategist {	//see Abstract_NavigationStrategist.h for more information
public:
	P3AT_NavigationStrategist(Abstract_RoadmapController *rc, Abstract_CommandHandler *ch, Abstract_WorldTranslator *wt);
	void mcDone(double rotation); 
	void mcDone(double rotation, double percentDone);
	void causeMotion(); 	
	void stopMotors(bool inclTurning);
	void updateWorldmap(double *sensorData);
protected:
	double getUnoccupied(double *sensData);
	WayPoint getAltRoute(double direct, double driveDist);
	double getVecLen(double vecX, double vecY);
	double currentRotation = 0;	//degrees of rotation relative to starting rotation
	WayPoint currentPosition;	//position relative to starting position (in meters)
	bool noOldWayPoint = true; //is set to true if no command has been fetched yet, or if the roadmap was empty during last fetch 
};