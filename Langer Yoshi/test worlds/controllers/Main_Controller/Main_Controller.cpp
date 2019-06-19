#include "src/stdafx.h"

#include "src/P3AT_MotorController.h"
#include "src/P3AT_RoadmapController.h"
#include "src/P3AT_CommandHandler.h"
#include "src/P3AT_SensorController.h"
#include "src/P3AT_NavigationStrategist.h"
#include "src/Mock_WorldmapController.h"
#include "src/Mock_WorldTranslator.h"
#include "src/Log.h"

#define TIME_STEP 32

int main(int argc, char **argv)
{
	//Empty out file with append = false and write initial message
	Log::emptyLog();

	//Initialize robot and controllers
	wb_robot_init();
	wb_robot_set_mode(WB_MODE_REMOTE_CONTROL, (void*)"-rp /dev/ttyUSB0");
	Abstract_MotorController *mc = new P3AT_MotorController();
	Abstract_RoadmapController *rc = new P3AT_RoadmapController();
	Abstract_CommandHandler *ch = new P3AT_CommandHandler(mc);
	Abstract_WorldTranslator *wt = new Mock_WorldTranslator();
	Abstract_NavigationStrategist *ns = new P3AT_NavigationStrategist(rc, ch, wt);
	Abstract_SensorController *sc = new P3AT_SensorController(ns);
	

	//Add coordinates to the roadmap that should be driven to 
	/*rc->addCoord(-10, 30, false);
	rc->addCoord(0, 0, false);
	rc->addCoord(1, 1, false);
	rc->addCoord(1, -1, false);
	rc->addCoord(-1, -1, false);
	rc->addCoord(-1, 1, false);
	rc->addCoord(0, 1, false);*/
    rc->addCoord(0, 1000, false);

	// control loop
	while (wb_robot_step(TIME_STEP) != -1) {
		mc->check();	//check if last command is done
		sc->checkSenses();	//checks if robot needs to stop and writes sensor data into worldmap (theoretically)
	}
	
	wb_robot_cleanup();

	return 0;
}
