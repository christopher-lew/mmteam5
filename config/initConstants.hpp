/**
 * This header instatiates global constants used throughout the Falcon.
 */

#ifndef INIT_CONSTANTS_H
#define INIT_CONSTANTS_H

#include "initModes.hpp"

/*
 * List of Constants
 *
 * VOLT_CONV: Conversion between ADC Value to Volts
 * MIN_VOLTAGE: Min Battery Voltage before we turn off the mouse
 */

#if _FALCON_CONFIG == 21
	#define VOLT_CONV 9.8

 	#if _BATTERIES == 2
		#define MIN_VOLTAGE 7.2
 	#elif _BATTERIES == 3
 		#define MIN_VOLTAGE 10.8
 	#endif	



#elif _FALCON_CONFIG == 20
	#define VOLT_CONV 9.8
	#define MIN_VOLTAGE 7.2

#endif

#endif