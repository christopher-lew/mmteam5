/**
 * Gyroscope implementation used to control an Analog Gyroscope (ADXRS620).
 */

#include "gyro.hpp"


 /* Constructor */
 Gyro::Gyro(PinName outZPin)
 	: outZ(outZPin) 
{
	this->currentADCAngle = 0.0;
}


float Gyro::getAngle()
{
	float currentAngle = this->currentADCAngle * G_SAMPLE_TIME;
	currentAngle = currentAngle * ADC_TO_DEG; // Convert ADC angle to degrees
	return currentAngle;
}


float Gyro::getADCRead()
{
	return outZ.read();
}


void Gyro::updateAngle()
{
	/*
	 * angular_speed = getADCRead() - G_OFFSET
	 * ADC_angle = angular_speed * G_SAMPLE_TIME
	 * totalAngle += ADC_angle
	 */
	this->currentADCAngle += outZ.read() - G_OFFSET;
}


void Gyro::resetAngle()
{
	this->currentADCAngle = 0.0;
}


void Gyro::start_sampling()
{	
	this->resetAngle();
	gyroTicker.attach(this, &Gyro::updateAngle, G_SAMPLE_TIME);
}


void Gyro::stop_sampling()
{
	gyroTicker.detach();
}
