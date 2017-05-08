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


float Gyro::getAngle()
{
	return currentAngle;
}


float Gyro::getADCRead()
{
	return outZ.read();
}


void Gyro::start_reading()
{	
	//TODO
}


void Gyro::stop_reading()
{
	//TODO
}


void Gyro::reset()
{
	this->currentAngle = 0.0;
}
