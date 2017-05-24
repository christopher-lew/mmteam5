/**
 * These basic functions are used to test that the Falcon and/or
 * the code is working correctly.
 */

#ifndef TEST_FUNCTIONS_H
#define TEST_FUNCTIONS_H

#include "mbed.h"
#include "../config/initModes.hpp"
#include "../config/initConstants.hpp"
#include "../config/initDevices.hpp"
#include "debug_io.hpp"

void cycleLEDs(float flashPeriod);

void cycleMFs(float flashPeriod);

void testBuzzer();

void testMotors_straight(float speed, int duration_ms);

void testMotors_rotate(float speed, int duration_ms);

void simpleDemo();

void ticker_switch1();
void ticker_switch2();
void tickerExample();


void IR_calibration(IRPair ir, int signal_delay_us, int signal_rest_us);

void Gyro_calibration(int num_samples, int sample_freq);

#endif