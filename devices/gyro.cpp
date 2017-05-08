/**
 * Gyroscope implementation used to control an Analog Gyroscope (ADXRS620).
 */

#include "gyro.hpp"


 /* Constructor */
 Gyro::Gyro(PinName outZPin)
 	: outZ(outZPin) 
{
	this->currentAngle = 0.0;
}


float Gyro::reset()
{
	this->currentAngle = 0.0;
}

float Gyro::read()
{
	float zRead = outZ.read();
	return zRead;
}