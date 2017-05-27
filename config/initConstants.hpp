/**
 * This header instatiates global constants used throughout the Falcon.
 */

#ifndef INIT_CONSTANTS_H
#define INIT_CONSTANTS_H

#include "initModes.hpp"


	// VOLT_CONV: Conversion between ADC Value to Volts
	// MIN_VOLTAGE: Min Battery Voltage before we turn off the mouse
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
		
		#define IR_SIGDELAY 6 // Wait for firing capacitor signal (usec)
		#define IR_SIGREST 75 // Allows firing cap to recharge

		
	#elif _IR_COEFF == 2
	 	// 18 ohms, 2.2uF
		#define IR_C13    0.000
		#define IR_C12   -0.001
		#define IR_C11    0.340
		#define IR_C00    9.356
		#define IR_C01  -24.567
		#define IR_C02   41.248
		#define IR_C03  -26.372
		
		#define IR_SIGDELAY 5 // Wait for firing capacitor signal (usec)
		#define IR_SIGREST 160 // Allows firing cap to recharge
		
	#endif



 	// Mouse states and state-dependent speeds
 	#define _OPERATOR_INPUT 0
	#define _EXPLORING 1
	#define _GO_HOME 2
	#define _SPEED_RUN 3
	#define _WALL_FOLLOWER -1

 	#define _EXPLORE_SPEED 0.12
 	#define _RUN_SPEED 0.3

 	#define BAUD_RATE 9600

#endif