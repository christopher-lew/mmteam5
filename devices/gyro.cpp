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


void Gyro::updateAngle()
{
	//TODO
}


void Gyro::resetAngle()
{
	this->currentAngle = 0.0;
}


void Gyro::start_reading()
{	
	this->resetAngle();
	gyroTicker.attach_us(this, &Gyro::updateAngle, G_SAMPLE_TIME);
}


void Gyro::stop_reading()
{
	gyroTicker.detach();
}
