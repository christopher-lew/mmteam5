#ifndef INIT_SENSORS_H
#define INIT_SENSORS_H

#include "mbed.h"
#include "ir.hpp"

#define VOLT_CONV 9.8 // DigOut Read -> Volts
#define MIN_VOLTAGE 7.3 // Min Battery Voltage 


// Sensor Classes
IRPair leftIR(PC_3, PC_5);
IRPair leftFrontIR(PC_1, PA_7);
IRPair rightFrontIR(PC_0, PA_6);
IRPair rightIR(PH_0, PA_4);


// Other IO Devices
AnalogIn battery(PA_3);

DigitalIn userButton(PC_10);

Serial pc(PA_9, PA_10);

PwmOut buzzer(PA_2);
//PwmOut ledMf(PC_6);


DigitalOut ledMf(PC_6);
DigitalOut ledRed(PB_15);
DigitalOut ledYellow(PB_14);
DigitalOut ledGreen(PB_13);


#endif