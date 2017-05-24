/**
 * Collection of functions that physically move the mouse from cell to cell.
 */

#ifndef DRIVER_H
#define DRIVER_H

#include "mbed.h"
#include "../config/initModes.hpp"
#include "../config/initConstants.hpp"
#include "../config/initDevices.hpp"
#include "debug_io.hpp"
#include "pid.hpp"
#include "testFunctions.hpp"

#define MVMT_WAIT_MS 100

extern PID_Controller pid;


void moveFalcon(char nextMove, float speed);

void forward(float speed);

void turnLeft(float speed);

void turnRight(float speed);

void turnAround(float speed);


char rightWallFollower();

char leftWallFollower();


#endif 