cmake_minimum_required(VERSION 3.12)
project(p3at_herbert CXX)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS -pthread)

set(WEBOTS_HOME D:/Programs/Webots/Webots)

set(WEBOTS_INCLUDE
        ${WEBOTS_HOME}/include/controller/c
        )

file(GLOB webots_libs
        "${WEBOTS_HOME}/msys64/mingw32/lib/*"
        )

find_library(WEBOTS_CONTROLLER_LIB Controller ${WEBOTS_HOME}/lib)

link_directories(${WEBOTS_HOME}/lib)
link_libraries(${webots_libs})

add_executable(yoshi
        ${source_files}
        Main_Controller.cpp
        Main_Controller.h
        src/Abstract_CommandHandler.h
        src/Abstract_MotorController.h
        src/Abstract_Motors.h
        src/Abstract_NavigationStrategist.h
        src/Abstract_RoadmapController.h
        src/Abstract_SensorController.h
        src/Command.h
        src/Log.cpp
        src/Log.h
        src/P3AT_Bumper.cpp
        src/P3AT_Bumper.h
        src/P3AT_CommandHandler.cpp
        src/P3AT_CommandHandler.h
        src/P3AT_MotorController.cpp
        src/P3AT_MotorController.h
        src/P3AT_Motors.cpp
        src/P3AT_Motors.h
        src/P3AT_NavigationStrategist.cpp
        src/P3AT_NavigationStrategist.h
        src/P3AT_RoadmapController.cpp
        src/P3AT_RoadmapController.h
        src/P3AT_SensorController.cpp
        src/P3AT_SensorController.h
        src/P3AT_Ultrasound.cpp
        src/P3AT_Ultrasound.h
        src/stdafx.cpp
        src/stdafx.h
        src/WayPoint.h)

target_link_libraries(yoshi ${CMAKE_DL_LIBS})
include_directories(${WEBOTS_INCLUDE})