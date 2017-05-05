/**
 * Gyroscope implementation used to control an Analog Gyroscope (ADXRS620).
 */

#include "gyro.hpp"


 /* Constructor */
 Gyro::Gyro(PinName outZPin)
 	: outZ(outZPin) { }


float Gyro::read()
{
	return outZ.read();
}