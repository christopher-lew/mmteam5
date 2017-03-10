/**
 * This header instatiates sensor classes and other misc devices needed to
 * operate the MF, and also defines a few constants.
 */

#ifndef INIT_SENSORS_H
#define INIT_SENSORS_H

#include "mbed.h"
#include "buzzer.hpp"
#include "ir.hpp"
#include "motor.hpp"
#include "encoder.hpp"

#define VOLT_CONV 9.8 // DigOut Read -> Volts
#define MIN_VOLTAGE 7.3 // Min Battery Voltage 


// Sensor Classes
Buzzer buzzer(PA_2);

IRPair leftIR(PC_3, PC_5);
IRPair leftFrontIR(PC_1, PA_7);
IRPair rightFrontIR(PC_0, PA_6);
IRPair rightIR(PH_0, PA_4);

Motor leftMotor(PC_8, PC_7);
Motor rightMotor(PB_9, PB_8);

Encoder leftEncoder(PB_3, PB_4);
Encoder rightEncoder(PB_7, PB_6); 


// LEDs
//PwmOut ledMf(PC_6);
DigitalOut ledMf(PC_6);
DigitalOut ledRed(PB_15);
DigitalOut ledYellow(PB_14);
DigitalOut ledGreen(PB_13);


// Other IO Devices
AnalogIn battery(PA_3);

DigitalIn userButton(PC_10);

Serial pc(PA_9, PA_10);


#endif