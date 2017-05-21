/**
 * Creates a Gyroscope class that allows for reading of the device.
 * ADXRS620: Clockwise rotation is positive!
 */


#ifndef GYRO_H
#define GYRO_H

#include "mbed.h"

#define G_OFFSET 0.5118
#define G_SAMPLE_TIME 0.001 // secs

#define mV_ADC 3300 // mV per ADC = (3.3V / 1.0)
#define degSec_mV 4.0 // angularSpeed per mV = [ (1 deg/sec) / 6 mV ]


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