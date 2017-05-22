/**
 * PID Controller for the Falcon.
 */

#ifndef PID_H
#define PID_H

#include "mbed.h"
#include "../config/initModes.hpp"
#include "../config/initConstants.hpp"
#include "../config/initDevices.hpp"
#include "testFunctions.hpp"

#define PID_LEFT_ALIGN 5.8 // centimeters
#define PID_RIGHT_ALIGN 6.1
#define PID_FRONT_ALIGN 4.5

#define COAST_SPEED 0.06


bool PID_keepStraight();

void PID_alignUsingSides(bool leftWall, bool rightWall);

void PID_alignToFrontWall();

void PID_HailMary();

void PID_turn(char direction);


int getEncoderDistance();

void resetEncoders();


#endif