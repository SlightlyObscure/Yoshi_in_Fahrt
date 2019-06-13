#pragma once

#include "WayPoint.h"

class Abstract_RoadmapController;	//RC
class Abstract_CommandHandler;		//CH
class Abstract_WorldTranslator;  //WT
//WorldmapController	WC

/*some definitions:
*starting position is x = 0, y = 0
*starting rotation (looking "north") is 0
*rotation is always a value within [0; 360[
*/

//This class acts as a central intersection between different parts of the robot and is responsible for forwarding
//information. New waypoints for the circumnavigation strategy are also calculated by the navigation strategist

class Abstract_NavigationStrategist {  //NS
public:
	Abstract_NavigationStrategist(Abstract_RoadmapController *rc, Abstract_CommandHandler *ch, Abstract_WorldTranslator *wt) {};
	virtual void mcDone(double rotation) = 0; //called when motor controller is done with last command; updates position from roadmap; calls causeMotion again
	virtual void mcDone(double rotation, double percentDone) = 0; //called if last command was interruted; updates position with "percentDone"
	virtual void causeMotion() = 0; //gets next destination from roadmap and calls commandMotor in CH
	virtual void stopMotors(bool inclTurning) = 0;	//stops movement, if sensors indicate an obstacle ahead
	virtual void updateWorldmap(double *sensorData) = 0;	//forwards data from SC to WC via WT
protected:
	Abstract_RoadmapController * roadmapController;
	Abstract_CommandHandler *commandHandler;
	Abstract_WorldTranslator *worldTranslator;
};

