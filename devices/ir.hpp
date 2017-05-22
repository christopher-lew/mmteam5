/**
 * Creates an IR Sensor class that includes private Emitter and Receiver objects. 
 * This class allows for a simple function call to utilize both physical sensors for each IR Pair.
 */

#ifndef IR_H
#define IR_H

#include "mbed.h"
#include "../config/initConstants.hpp"

#define IR_SAMPLES 3

#define FRONT_WALL_LIMIT 11
#define SIDE_WALL_LIMIT 13 // If a wall is closer than this, then it is touching the currently occupied cell
#define CELL_LENGTH 18.0 // each cell is 18 cm long


// Class for the IR Transmitter and Receiver Pair
class IRPair
{	
public:
	float readLog[IR_SAMPLES]; // used for logging IR read values
	
	IRPair(PinName rxPin, PinName txPin, bool frontStatus);
	
	bool adjWall(); 
	float distToWall(); // Returns dist in cm
	int cellsToWall(); // Returns how many cells away a wall is
	float calibration(int signal_delay_us, int signal_rest_us);
	
private:
	bool isFrontIR;
	float wall_limit;	

	AnalogIn 	IR_Receiver;
	DigitalOut	IR_Emitter;

	float fireAndRead();
	float calib_fireAndRead(int signal_delay_us, int signal_rest_us);
	float getDistance(float ADC_read);
};

#endif 