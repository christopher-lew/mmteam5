/**
 * IR Sensor class implementation. Utilizes both physical sensors in function implementations.
 */

#include "ir.hpp"


/* Constructor */
IRPair::IRPair(PinName rxPin, PinName txPin)
	: IR_Receiver(rxPin), IR_Emitter(txPin) 
{
	this->IR_Emitter.write(0);
}


/* Fires a single cycle of the IR Pair and returns the ADC read value. */
float IRPair::fireAndRead()
{
	IR_Emitter.write(1);
	wait_us(IR_SIGDELAY); // Wait for firing capacitor

	float read = IR_Receiver.read();
	IR_Emitter.write(0);
	wait_us(IR_SIGREST); // Recharge firing capacitor

	return read;
}


/* Use polynomial regression formula to generate distance to wall from ADC reading. */
float IRPair::getDistance(float ADC_read)
{
	float dist = 0;
	float square = ADC_read * ADC_read;
	float cube = square * ADC_read;
	
	dist += IR_C13 / cube;
	dist += IR_C12 / square;
	dist += IR_C11 / ADC_read;
	dist += IR_C00;
	dist += IR_C01 * ADC_read;
	dist += IR_C02 * square;
	dist += IR_C03 * cube;
		
	return dist;
}


/* Returns True(1) or False(0) if there is a wall right next to the sensor */
int IRPair::adjWall()
{
	fireAndRead(); // Noisy initial read
	float read = fireAndRead();
	float dist = getDistance(read);

	if (dist < ADJ_WALL_LIMIT) {
		return 1;
	}
	else {
		return 0;
	}
}

	
/*
 * Gets the distance to the wall.
 * Returns:
 *	dist - calculated distance in cm to the wall
 */
float IRPair::distToWall()
{
	float avgRead = 0;
	fireAndRead(); // Noisy initial read
	
	for (int i = 0; i < IR_SAMPLES; i++) {
		readLog[i] = fireAndRead();
		avgRead += readLog[i];
	}
	
	avgRead /= IR_SAMPLES;
		
	return getDistance(avgRead);
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