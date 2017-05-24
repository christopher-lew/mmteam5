/**
 * Creates Motor class that allows the utilization of a single motor.
 * Functions include a go() and stop() function.
 * Possibly might include PID/speed profile functions/constants later on.
 */

#ifndef MOTOR_H
#define MOTOR_H

#include "mbed.h"

#define ACC_STEPS 4
#define ACC_WAIT_MS 1
#define ACC_INSTANT_WAIT_US 200
#define MOTOR_PERIOD_US 50


class Motor
{
public:
	float curSpeed;

	Motor(PinName dirPin, PinName pwmPin);
	void instantAccel(float newSpeed);
	void instantStop();
	void accel(float newSpeed);
	void stop();

private:
	PwmOut pwm_ChA;
	PwmOut pwm_ChB;
	
	//int invFwd;
	//int invBkwd;
};

#endif