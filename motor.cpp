#include "motor.hpp"


Motor::Motor(PinName dirPin, PinName pwmPin)
	: DirCtrl(dirPin), PwmCtrl(pwmPin) 
{
	// TODO - Read PwmOut.h to figure out what constants should be used, then #define them
	this->PwmCtrl.period(0.001);
	this->PwmCtrl.write(0);
	this->DirCtrl.write(0);
	this->speed = 0;
}

void Motor::go(float speed) 
{
	
}
	
void Motor::stop()
{
	this->go(0);
}
	
