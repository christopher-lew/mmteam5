#include "ir.hpp"

// Initialize constant array COEFF, in the IRPair class (and all IRPair objects)
// COEFF = [x^-3, x^-2, x^-1, x^0, x^1, x^2, x^3]
const float IRPair::COEFF[] = {0.218, -5.510, 55.011, -229.934, 506.986, -502.862, 177.713};

/*
 * Constructor for IRPair. Initializes physical sensor pair.
 */
IRPair::IRPair(PinName rxPin, PinName txPin)
	: IR_Receiver(rxPin), IR_Emitter(txPin) { }

/*
 * Gets the distance to the wall.
 * Returns:
 *	dist - calculated distance in cm to the wall
 */
float IRPair::dist_to_wall()
{
	float avgRead = 0;
	
	for (int i = 0; i < IR_SAMPLES; i++) {
		// Turn on IR
		this->IR_Emitter.write(1);
		
		// Wait for firing capacitor
		wait_us(IR_SIGDELAY);
		
		// Read IR 
		this->readLog[i] = this->IR_Emitter.read();
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
	
	dist += this->COEFF[0] / cube;
	dist += this->COEFF[1] / square;
	dist += this->COEFF[2] / avgRead;
	dist += this->COEFF[3];
	dist += this->COEFF[4] * avgRead;
	dist += this->COEFF[5] * square;
	dist += this->COEFF[6] * cube;
		
	return dist;
}