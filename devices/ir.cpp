/**
 * IR Sensor class implementation. Utilizes both physical sensors in function implementations.
 */

#include "ir.hpp"


/* Constructor */
IRPair::IRPair(PinName rxPin, PinName txPin)
	: IR_Receiver(rxPin), IR_Emitter(txPin) { }

	
/*
 * Gets the distance to the wall.
 * Returns:
 *	dist - calculated distance in cm to the wall
 */
float IRPair::distToWall()
{
	float avgRead = 0;
	
	for (int i = 0; i < IR_SAMPLES; i++) {
		// Turn on IR
		this->IR_Emitter.write(1);
		
		// Wait for firing capacitor
		wait_us(IR_SIGDELAY);
		
		// Read IR 
		this->readLog[i] = this->IR_Receiver.read();
		avgRead += this->readLog[i];
		
		// Turn off IR
		this->IR_Emitter.write(0);
		
		// Recharge
		wait_us(IR_SIGREST);
	}
	avgRead /= IR_SAMPLES;
	
	// Use polynomial regression formula to generate distance to wall
	float dist = 0;
	float square = avgRead * avgRead;
	float cube = square * avgRead;
	
	dist += IR_C13 / cube;
	dist += IR_C12 / square;
	dist += IR_C11 / avgRead;
	dist += IR_C00;
	dist += IR_C01 * avgRead;
	dist += IR_C02 * square;
	dist += IR_C03 * cube;
		
	return dist;
}


/*
 * Gets the distance to the wall in number of cells.
 * This function is designed to be used for exploration and 
 * mapping of the maze, not for PID or alignment.
 * Returns:
 *	cells - distance to the wall in number of cells
 *		0 = the wall is touching the currently occupied cell
 *		1 = the wall is touching the end of the adjacent cell
 *
 * TODO: 
 *	- Determine MAX_WALLS_AWAY (3 or 4?)
 *	- Determine faster algorithm
 */
int IRPair::cellsToWall()
{
	float dist = this->distToWall();
	int cellsAway;
	
	if (dist < ADJ_WALL_LIMIT + CELL_LENGTH*0) {
		cellsAway = 0;
	}
	else if (dist < ADJ_WALL_LIMIT + CELL_LENGTH*1) {
		cellsAway = 1;
	}
	else if (dist < ADJ_WALL_LIMIT + CELL_LENGTH*2) {
		cellsAway = 2;
	}
	else if (dist < ADJ_WALL_LIMIT + CELL_LENGTH*3) {
		cellsAway = 3;
	}
	else {
		cellsAway = 4;
	}
	
	return cellsAway;
}