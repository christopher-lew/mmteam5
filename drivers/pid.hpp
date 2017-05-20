/**
 *
 */

#ifndef PID_H
#define PID_H

#include "mbed.h"
#include "../config/initModes.hpp"
#include "../config/initConstants.hpp"
#include "../config/initDevices.hpp"

#define PID_ALIGN_FRONT_DIST 3 // centimeters


bool PID_keepStraight();

void PID_alignToFrontWall();

void PID_alignUsingSides(bool leftWall, bool rightWall);

void PID_HailMary();


void PID_turn(char direction);


#endif