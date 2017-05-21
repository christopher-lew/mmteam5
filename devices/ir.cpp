/**
 * IR Sensor class implementation. Utilizes both physical sensors in function implementations.
 */

#include "ir.hpp"


/* Constructor */
IRPair::IRPair(PinName rxPin, PinName txPin, bool frontStatus)
	: IR_Receiver(rxPin), IR_Emitter(txPin), isFrontIR(frontStatus)
{
	this->IR_Emitter.write(0);
	if (this->isFrontIR) {
		this->wall_limit = FRONT_WALL_LIMIT;
	}
	else {
		this->wall_limit = SIDE_WALL_LIMIT;
	}
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


/* Returns True or False if there is a wall right next to the sensor */
bool IRPair::adjWall()
{
	fireAndRead(); // Noisy initial read
	float read = fireAndRead();
	float dist = getDistance(read);

	if (dist < this->wall_limit && dist >= 0) {
		return true;
	}
	else {
		return false;
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
	this->fireAndRead(); // Noisy initial read
	
	for (int i = 0; i < IR_SAMPLES; i++) {
		readLog[i] = this->fireAndRead();
		avgRead += readLog[i];
	}
	
	avgRead /= IR_SAMPLES;
		
	return this->getDistance(avgRead);
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
	
	if (dist < this->wall_limit + CELL_LENGTH*0) {
		cellsAway = 0;
	}
	else if (dist < this->wall_limit + CELL_LENGTH*1) {
		cellsAway = 1;
	}
	else if (dist < this->wall_limit + CELL_LENGTH*2) {
		cellsAway = 2;
	}
	else if (dist < this->wall_limit + CELL_LENGTH*3) {
		cellsAway = 3;
	}
	else {
		cellsAway = 4;
	}
	
	return cellsAway;
}





float IRPair::calib_fireAndRead(int signal_delay_us, int signal_rest_us)
{
	IR_Emitter.write(1);
	wait_us(signal_delay_us); // Wait for firing capacitor

	float read = IR_Receiver.read();
	IR_Emitter.write(0);
	wait_us(signal_rest_us); // Recharge firing capacitor

	return read;
}

float IRPair::calibration(int signal_delay_us, int signal_rest_us)
{
	float avgRead = 0;
	this->calib_fireAndRead(signal_delay_us, signal_rest_us); // Noisy initial read
	
	for (int i = 0; i < IR_SAMPLES; i++) {
		readLog[i] = this->calib_fireAndRead(signal_delay_us, signal_rest_us);
		avgRead += readLog[i];
	}
	
	avgRead /= IR_SAMPLES;
		
	return this->getDistance(avgRead);
}