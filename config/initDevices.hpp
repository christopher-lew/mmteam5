/**
 * This header instatiates sensor classes and other misc devices needed to
 * operate the MF, and also defines a few constants.
 */

#ifndef INIT_DEVICES_H
#define INIT_DEVICES_H

#include "mbed.h"
#include "initModes.hpp"
#include "initConstants.hpp"
#include "../devices/buzzer.hpp"
#include "../devices/ir.hpp"
#include "../devices/motor.hpp"
#include "../devices/encoder.hpp"


// Sensor Classes
extern Buzzer buzzer;
/*
IRPair leftIR(PB_0, PC_9;
IRPair leftFrontIR(PC_5, PA_4);
IRPair rightFrontIR(PC_4, PC_1);
IRPair rightIR(PA_6, PC_14);
IRPair testIR(PA_7, PH_0);

Motor leftMotor(PB_5, PB_4);
Motor rightMotor(PB_9, PB_8);

Encoder leftEncoder(PB_10, PA_5);
Encoder rightEncoder(PA_0, PA_1); 
*/

// LEDs
extern PwmOut ledMf;
extern DigitalOut ledRed;
extern DigitalOut ledYellow;
extern DigitalOut ledGreen;


// Other IO Devices
extern AnalogIn battery;

extern Serial pc;

//extern DigitalIn userButton;


#endif