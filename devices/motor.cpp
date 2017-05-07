/**
 * Motor class implementation to control a single Faulhaber motor.
 */

#include "motor.hpp"


/* Constructor */
Motor::Motor(PinName PwmA, PinName PwmB)
	: pwm_ChA(PwmA), pwm_ChB(PwmB) 
{
	this->pwm_ChA.write(0); // 0% duty-cycle
	this->pwm_ChB.write(0);
	this->pwm_ChA.period_ms(1);
	this->pwm_ChB.period_ms(1);
}


void Motor::go(float speed) 
{
	/*
	// Forwards
	if (speed > 0) {
		this->pwm_ChA.write(0);
		this->pwm_ChB.write(speed);
	}

	// Backwards
	else {
		this->pwm_ChA.write(-speed);
		this->pwm_ChB.write(0);
	}
	*/

	// Forwards
	if (speed > 0) {
		this->pwm_ChA.write(1-speed);
		this->pwm_ChB.write(1);
	}

	// Backwards
	else {
		this->pwm_ChA.write(1);
		this->pwm_ChB.write(1+speed);
	}

	this->pwm_ChA.period_ms(1);
	this->pwm_ChB.period_ms(1);	
}


void Motor::stop()
{
	this->pwm_ChA.write(0);
	this->pwm_ChB.write(0);
	this->pwm_ChA.period_ms(1);
	this->pwm_ChB.period_ms(1);
}
	
