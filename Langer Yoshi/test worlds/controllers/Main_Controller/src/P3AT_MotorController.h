#pragma once

#include "Abstract_MotorController.h"
#include "P3AT_Motors.h"

class Abstract_CommandHandler;	//CH

class P3AT_MotorController : public Abstract_MotorController {	//see Abstract_MotorController.h for more information
public:
	P3AT_MotorController();
	void doCommand(Command cmd);
	void stop(bool inclTurning);
	double getIntermediate(void);
	bool getIsTurning();
	void check();
	void addCommandHandler(Abstract_CommandHandler *ch);
private:
	void rotate(double degrees);	//calls rotate in Motors
	void drive(double metres);		//calls drive in Motors
	double calcDistance(bool turning);		//calls getDonePercentage in Motors
	void fetchNextCommand();		//requests new command from CH
	void reportStop();				//does the same as fetchNextCommand() except it forwards donePercentage and causes NS to use circumnavigation strategy

	Abstract_CommandHandler *commandHandler;
	Command currentCommand;		//latest command received from CH
	bool _isStopped = false;	//is true if the robot had to stop prematurely and causes alternate navigation strategy
	bool _isVeryStopped = false;	//is set to true when _isStopped is if bumpers caused the robot to stop, prevents further movement
	bool _isTurning = true;		//is true if the rotate part of the current command is not yet done
	
};