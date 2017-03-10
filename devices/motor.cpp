/**
 * Motor class implementation to control a single Faulhaber motor.
 */

#include "motor.hpp"


/* Constructor */
Motor::Motor(PinName dirPin, PinName pwmPin)
	: ctrlDir(dirPin), ctrlPwm(pwmPin) 
{
	// TODO - Read PwmOut.h to figure out what constants should be used, then #define them
	this->ctrlPwm.period(0.001);
	this->ctrlPwm.write(0);
	this->ctrlDir.write(0);
	this->speed = 0;
}


void Motor::go(float speed) 
{
	
}


void Motor::stop()
{
	this->go(0);
}
	
