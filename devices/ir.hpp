/**
 * Creates an IR Sensor class that includes private Emitter and Receiver objects. 
 * This class allows for a simple function call to utilize both physical sensors for each IR Pair.
 */

#ifndef IR_H
#define IR_H

#include "mbed.h"
#include "../config/initConstants.hpp"

#define IR_SAMPLES 5
#define IR_SIGDELAY 6 // Wait for firing capacitor signal (usec)
#define IR_SIGREST 75 // Allows firing cap to recharge

#define ADJ_WALL_LIMIT 10 // If a wall is closer than this, then it is touching the currently occupied cell
#define CELL_LENGTH 18 // each cell is 18 cm long


// Class for the IR Transmitter and Receiver Pair
class IRPair
{	
public:
	float readLog[IR_SAMPLES]; // used for logging IR read values
	
	IRPair(PinName rxPin, PinName txPin);
	
	float distToWall(); // Returns dist in cm
	int cellsToWall(); // Returns how many cells away a wall is
	
private:
	AnalogIn 	IR_Receiver;
	DigitalOut	IR_Emitter;
};

#endif 