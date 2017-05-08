/**
 * This header utilizes the pc serial object instantiated in initSensors,
 * and several functions that use pc to print the status of different 
 * sensors & devices on the mouse.
 */

#ifndef DEBUG_IO_H
#define DEBUG_IO_H

#include "mbed.h"
#include "../config/initModes.hpp"
#include "../config/initConstants.hpp"
#include "../config/initDevices.hpp"


// Debugging Print Statements

void print_battery();

void print_ir(IRPair ir);

void print_ir_all();

void print_encoder(char encChoice);

void print_both_encoders(char turnDirection, int leftRead, int rightRead);

void print_gyro();


#endif