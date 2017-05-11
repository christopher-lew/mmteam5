/**
 * Creates a Gyroscope class that allows for reading of the device.
 */


#ifndef GYRO_H
#define GYRO_H

#include "mbed.h"

#define G_OFFSET 0.515
#define G_SAMPLE_TIME 50 // usecs


class Gyro
{
public:	
	Gyro(PinName outZPin);
	
	float getAngle();
	float getADCRead();
	
	void start_reading();
	void stop_reading();

private:
	float currentAngle;

	AnalogIn outZ;
	Ticker gyroTicker;

	void updateAngle();
	void resetAngle();
};

#endif