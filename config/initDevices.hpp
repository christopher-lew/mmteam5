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
#include "../devices/gyro.hpp"


// Sensor Classes
extern Buzzer buzzer;

extern IRPair leftIR;
extern IRPair frontLeftIR;
extern IRPair frontRightIR;
extern IRPair rightIR;
extern IRPair testIR;

extern Motor leftMotor;
extern Motor rightMotor;

extern Encoder leftEncoder;
extern Encoder rightEncoder; 

extern Gyro gyro;


// LEDs
extern PwmOut ledMf;
extern DigitalOut ledRed;
extern DigitalOut ledYellow;
extern DigitalOut ledGreen;


// Other IO Devices
extern AnalogIn battery;

extern Serial bluetooth;

extern DigitalIn userButton;


#endif