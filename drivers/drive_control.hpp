/**
 * 
 */

#ifndef DRIVER_H
#define DRIVER_H

#include "mbed.h"
#include "../config/initModes.hpp"
#include "../config/initConstants.hpp"
#include "../config/initDevices.hpp"
#include "debug_io.hpp"
#include "pid.hpp"


int getEncoderDistance();

void resetEncoders();


void moveFalcon(char nextMove, float speed);

void forward(float speed);

void turnLeft(float speed);

void turnRight(float speed);


char rightWallFollower();


#endif 