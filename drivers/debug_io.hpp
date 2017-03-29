/**
 * This header utilizes the pc serial object instantiated in initSensors,
 * and several functions that use pc to print the status of different 
 * sensors & devices on the mouse.
 */

#ifndef DEBUG_IO_H
#define DEBUG_IO_H

#include "mbed.h"
#include "../config/initSensors.hpp"


extern Serial pc;

// Debugging Print Statements

void print_battery();

void print_ir(IRPair ir);

void print_ir_all();

void print_encoder();

void print_motor();

#endif