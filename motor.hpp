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
	DigitalOut DirCtrl;
	PwmOut PwmCtrl;
	float speed;
};

#endif