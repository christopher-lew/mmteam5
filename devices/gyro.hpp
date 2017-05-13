/**
 * Creates a Gyroscope class that allows for reading of the device.
 */


#ifndef GYRO_H
#define GYRO_H

#include "mbed.h"
#include "../config/initConstants.hpp"


class Gyro
{
public:	
	Gyro(PinName outZPin);
	float read();

private:
	AnalogIn outZ;
};

#endif