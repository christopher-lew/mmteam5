/**
 *
 */

#ifndef PID_H
#define PID_H

#include "mbed.h"
#include "../config/initModes.hpp"
#include "../config/initConstants.hpp"
#include "../config/initDevices.hpp"
#include "debug_io.hpp"


void PID_keepStraight();

void alignFront();

void alignSides(int leftWall, int rightWall);

void PID_turn(char direction);


#endif