/*
 * This header instatiates a pc serial object, and several functions
 * that use pc to print the status of different sensors & devices on the mouse.
 */

#ifndef DEBUG_IO_H
#define DEBUG_IO_H

#include "mbed.h"
#include "initSensors.hpp"


extern Serial pc;

// Debugging Print Statements

void print_battery() {
	float Vbat = battery.read();
	pc.print("Battery: %1.2f (%1.2f V)\r\n", Vbat, Vbat*VOLT_CONV);
}

void print_ir(IRPair ir) {
	for (int i = 0; i < IR_SAMPLES; i++) {
		pc.printf("%3.9f\r\n", ir.readLog[i]);
	}
}

void print_ir_all();

void print_encoder();

void print_motor();

#endif