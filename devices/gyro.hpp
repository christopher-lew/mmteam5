/**
 * Creates a Gyroscope class that allows for reading of the device.
 * ADXRS620: Clockwise rotation is positive!
 */


#ifndef GYRO_H
#define GYRO_H

#include "mbed.h"

#define G_OFFSET 0.515
#define G_SAMPLE_TIME 0.001 // secs
#define ADC_TO_DEG 100 // converts gyro ADC angle to degrees


class Gyro
{
public:	
	Gyro(PinName outZPin);
	
	float getAngle();
	float getADCRead();
	
	void start_sampling();
	void stop_sampling();

private:
	float currentADCAngle; // In ADC units 

	AnalogIn outZ;
	Ticker gyroTicker;

	void updateAngle();
	void resetAngle();
};

#endif