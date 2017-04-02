/**
 * These basic functions are used to test that the Falcon and/or
 * the code is working correctly.
 */

#ifndef TEST_FUNCTIONS_H
#define TEST_FUNCTIONS_H

#include "mbed.h"
#include "../config/initModes.hpp"
#include "../config/initDevices.hpp"

void cycleLEDs(float flashPeriod);

void cycleMFs(float flashPeriod);

void testBuzzer();

#endif