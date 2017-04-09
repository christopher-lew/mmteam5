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
	#define VOLT_CONV 16.7

 	#if _BATTERIES == 2
		#define MIN_VOLTAGE 7.2
 	#elif _BATTERIES == 3
 		#define MIN_VOLTAGE 10.8
 	#endif	



#elif _FALCON_CONFIG == 20
	#define VOLT_CONV 9.8
	#define MIN_VOLTAGE 7.2

#endif

// Declare IR Coefficients
// COEFF = [x^-3, x^-2, x^-1, x^0, x^1, x^2, x^3]
#if _IR_COEFF == 1
	#define IR_C13    0.218
	#define IR_C12   -5.510
	#define IR_C11   55.011
	#define IR_C00 -229.934
	#define IR_C01  506.986
	#define IR_C02 -502.862
	#define IR_C03  177.713
#endif

#endif