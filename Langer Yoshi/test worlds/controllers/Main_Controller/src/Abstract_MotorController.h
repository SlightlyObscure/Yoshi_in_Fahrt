#pragma once

#include "WayPoint.h"
#include "Command.h"
#include "Abstract_Motors.h"

class Abstract_CommandHandler;	//CH

//This class receives commands from the CH to execute them, has a function that is called in the
//main loop to check if the previous command is done and can return info needed to calculate the 
//robot's position during command execution

class Abstract_MotorController {	//MC
public:
	Abstract_MotorController() {};
	virtual void doCommand(Command cmd) = 0;	//if rotation is not yet done, do rotation; else do forward movement
	virtual void stop(bool inclTurning) = 0;	//stops motors and sets variable, so that an appropriate navigation strategy may be attempted; inclTurning should be true if the robot should stop even if it is turning
	virtual double getIntermediate(void) = 0;	//returns done percentage of last command while it's being executed
	virtual bool getIsTurning() = 0;	//returns true if the robot is in turning mode and false if it's in driving mode
	virtual void check() = 0;	//is called in main loop to check if the last command is done -> if it is the next command is fetched
	virtual void addCommandHandler(Abstract_CommandHandler *ch) = 0;
protected:
	Abstract_Motors *Motors;
};