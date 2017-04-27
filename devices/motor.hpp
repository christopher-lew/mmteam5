/**
 * Creates Motor class that allows the utilization of a single motor.
 * Functions include a go() and stop() function.
 * Possibly might include PID/speed profile functions/constants later on.
 */

#ifndef MOTOR_H
#define MOTOR_H

#include "mbed.h"

class Motor
{
public:
	Motor(PinName dirPin, PinName pwmPin);
	void go(float speed);
	void stop();

private:
	PwmOut pwm_ChA;
	PwmOut pwm_ChB;
	//!!!float speed;
};

#endif