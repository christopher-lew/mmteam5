/**
 * Motor class implementation to control a single Faulhaber motor.
 */

#include "motor.hpp"


Motor::Motor(PinName PwmA, PinName PwmB)
	: pwm_ChA(PwmA), pwm_ChB(PwmB) 
{
	this->curSpeed = 0.0;
	this->pwm_ChA.write(0); // 0% duty-cycle
	this->pwm_ChB.write(0);
	this->pwm_ChA.period_ms(1);
	this->pwm_ChB.period_ms(1);
}


void Motor::stop()
{
	this->pwm_ChA.period_ms(1);
	this->pwm_ChB.period_ms(1);

	float speed_step = (0.0 - this->curSpeed)/ACC_STEPS;

	// Currently going forwards
	if (this->curSpeed > 0) {
		this->pwm_ChA.write(0);
		
		for (int i = 0; i < ACC_STEPS; i++) {
			wait_ms(ACC_WAIT_MS);
			this->curSpeed += speed_step;
			this->pwm_ChB.write(this->curSpeed);
		}
	}

	// Currently going backwards
	else {
		this->pwm_ChB.write(0);

		for (int i = 0; i < ACC_STEPS; i++) {
			wait_ms(ACC_WAIT_MS);
			this->curSpeed += speed_step;
			this->pwm_ChA.write(this->curSpeed);
		}
	}
}


void Motor::go(float newSpeed) 
{
	float speed_step = (newSpeed - this->curSpeed)/ACC_STEPS;
	this->pwm_ChA.period_ms(1);
	this->pwm_ChB.period_ms(1);	

	// Forwards
	if (newSpeed > 0) {
		this->pwm_ChA.write(0);

		for (int i = 0; i < ACC_STEPS; i++) {
			wait_ms(ACC_WAIT_MS);
			this->curSpeed += speed_step;
			this->pwm_ChB.write(this->curSpeed);
		}
	}

	// Backwards
	else {
		this->pwm_ChB.write(0);

		for (int i = 0; i < ACC_STEPS; i++) {
			wait_ms(ACC_WAIT_MS);
			this->curSpeed += speed_step;
			this->pwm_ChA.write(this->curSpeed);
		}		
	}
}


/* 
Motor::Motor(PinName PwmA, PinName PwmB, int iFwd, int iBck)
	: pwm_ChA(PwmA), pwm_ChB(PwmB), invFwd(iFwd), invBkwd(iBck) 
{
	this->curSpeed = 0.0;
	this->pwm_ChA.write(0); // 0% duty-cycle
	this->pwm_ChB.write(0);
	this->pwm_ChA.period_ms(1);
	this->pwm_ChB.period_ms(1);
}


void Motor::go(float newSpeed) 
{
	// Forwards
	if (newSpeed > 0) {
		if (invFwd) {
			this->pwm_ChA.write(1-newSpeed);
			this->pwm_ChB.write(1);
		}
		else {
			this->pwm_ChA.write(0);
			this->pwm_ChB.write(newSpeed);
		}
	}

	// Backwards
	else {
		if (invBkwd) {
			this->pwm_ChA.write(1);
			this->pwm_ChB.write(1+newSpeed);
		}
		else {
			this->pwm_ChA.write(-newSpeed);
			this->pwm_ChB.write(0);
		}
	}

	this->pwm_ChA.period_ms(1);
	this->pwm_ChB.period_ms(1);	
}
*/