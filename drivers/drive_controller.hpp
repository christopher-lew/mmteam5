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


int getEncoderDistance();

void resetEncoders();

void forward();

void turnLeft();

void turnRight();

void turnAround();



#endif 