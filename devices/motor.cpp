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
	this->pwm_ChA.period_us(MOTOR_PERIOD_US);
	this->pwm_ChB.period_us(MOTOR_PERIOD_US);
}


/* Instantly changes the motor speed without easing into it */
void Motor::instantAccel(float newSpeed)
{
	this->pwm_ChA.period_us(MOTOR_PERIOD_US);
	this->pwm_ChB.period_us(MOTOR_PERIOD_US);

	// Request to go forwards
	if (newSpeed > 0) {
		this->pwm_ChA.write(0);
		// If current speed is in the opposite direction, stop the motor first
		if (this->curSpeed < 0) {
			this->curSpeed = 0;
			this->pwm_ChB.write(this->curSpeed);
			wait_us(ACC_INSTANT_WAIT_US);
		}

		this->curSpeed = newSpeed;
		this->pwm_ChB.write(this->curSpeed);
	}

	// Request to go backwards
	else {
		this->pwm_ChB.write(0);
		// If current speed is in the opposite direction, stop the motor first
		if (this->curSpeed > 0) {
			this->curSpeed = 0;
			this->pwm_ChA.write(this->curSpeed);
			wait_us(ACC_INSTANT_WAIT_US);
		}

		this->curSpeed = newSpeed;
		this->pwm_ChB.write(this->curSpeed*-1);	
	}
}


/* Instantly stop the motors */
void Motor::instantStop() 
{
	this->pwm_ChA.period_us(MOTOR_PERIOD_US);
	this->pwm_ChB.period_us(MOTOR_PERIOD_US);
	this->curSpeed = 0;
	this->pwm_ChA.write(0);
	this->pwm_ChB.write(0);
}


/* Accelerates the motor to the given speed in ACC_STEPS */
void Motor::accel(float newSpeed) 
{
	float speed_step;
	this->pwm_ChA.period_us(MOTOR_PERIOD_US);
	this->pwm_ChB.period_us(MOTOR_PERIOD_US);

	// Forwards
	if (newSpeed > 0) {
		this->pwm_ChA.write(0);
		// If current speed is in the opposite direction, stop the motor first
		if (this->curSpeed < 0) {
			this->curSpeed = 0;
			this->pwm_ChB.write(this->curSpeed);
			wait_us(ACC_INSTANT_WAIT_US);
		}
		speed_step = (newSpeed - this->curSpeed)/ACC_STEPS;

		for (int i = 0; i < ACC_STEPS; i++) {
			wait_ms(ACC_WAIT_MS);
			this->curSpeed += speed_step;
			this->pwm_ChB.write(this->curSpeed);
		}
	}

	// Backwards
	else {
		this->pwm_ChB.write(0);
		// If current speed is in the opposite direction, stop the motor first
		if (this->curSpeed > 0) {
			this->curSpeed = 0;
			this->pwm_ChA.write(this->curSpeed);
			wait_us(ACC_INSTANT_WAIT_US);
		}

		speed_step = (newSpeed - this->curSpeed)/ACC_STEPS;

		for (int i = 0; i < ACC_STEPS; i++) {
			wait_ms(ACC_WAIT_MS);
			this->curSpeed += speed_step;
			this->pwm_ChA.write(this->curSpeed*-1);
		}		
	}
}


/* Slows the motor to a stop, rather than an abrupt stop */
void Motor::stop()
{
	this->pwm_ChA.period_us(MOTOR_PERIOD_US);
	this->pwm_ChB.period_us(MOTOR_PERIOD_US);

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

/* 
Motor::Motor(PinName PwmA, PinName PwmB, int iFwd, int iBck)
	: pwm_ChA(PwmA), pwm_ChB(PwmB), invFwd(iFwd), invBkwd(iBck) 
{
	this->curSpeed = 0.0;
	this->pwm_ChA.write(0); // 0% duty-cycle
	this->pwm_ChB.write(0);
	this->pwm_ChA.period_us(MOTOR_PERIOD_US);
	this->pwm_ChB.period_us(MOTOR_PERIOD_US);
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

	this->pwm_ChA.period_us(MOTOR_PERIOD_US);
	this->pwm_ChB.period_us(MOTOR_PERIOD_US);
}
*/