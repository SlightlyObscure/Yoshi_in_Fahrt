cmake_minimum_required(VERSION 3.12)
project(p3at_herbert CXX)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS -pthread)

set(WEBOTS_HOME /usr/local/webots)

set(WEBOTS_INCLUDE
        ${WEBOTS_HOME}/include/controller/c
        )

file(GLOB webots_libs
        "${WEBOTS_HOME}/lib/*.so*"
        )

file(GLOB_RECURSE all_yosh
        "src/*")

find_library(WEBOTS_CONTROLLER_LIB Controller ${WEBOTS_HOME}/lib)

link_directories(${WEBOTS_HOME}/lib)
link_libraries(${webots_libs})

add_executable(Main_Controller
        ${source_files}
        Main_Controller.cpp
        Main_Controller.h
        ${all_yosh})

target_link_libraries(Main_Controller ${CMAKE_DL_LIBS})
include_directories(${WEBOTS_INCLUDE})