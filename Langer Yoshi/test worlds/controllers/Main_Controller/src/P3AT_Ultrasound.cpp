#include "stdafx.h"
#include "P3AT_Ultrasound.h"
#include "Log.h"



P3AT_Ultrasound::P3AT_Ultrasound() {
	int time_step = wb_robot_get_basic_time_step();
	char sensor_name[5] = "";
	int i;

	for (i = 0; i < MAX_SENSOR_NUMBER; ++i) {
		sprintf(sensor_name, "so%d", i);
		sensors[i] = wb_robot_get_device(sensor_name);
		wb_distance_sensor_enable(sensors[i], time_step);
	}
}

double *P3AT_Ultrasound::getData() {
	double *data = new double[MAX_SENSOR_NUMBER];
	for (int i = 0; i < MAX_SENSOR_NUMBER; i++) {
		data[i] = wb_distance_sensor_get_value(sensors[i]);
		std::cout << "Sensor value: " << data[i] << std::endl;
	}
	return data;
}