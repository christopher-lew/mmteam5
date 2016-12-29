#ifndef IR_H
#define IR_H

#include "mbed.h"

#define IR_SAMPLES 5
#define IR_SIGDELAY 6 // Wait for firing capacitor signal (usec)
#define IR_SIGREST 75 // Allows firing cap to recharge


// Class for the IR Transmitter and Receiver Pair
class IRPair
{	
public:
	static const float COEFF[]; // Coefficients found using linear regression (volts->cm)
	float readLog[IR_SAMPLES]; // used for logging IR read values
	
	IRPair(PinName rxPin, PinName txPin);
	
	float dist_to_wall(); // Returns dist in cm
	
private:
	AnalogIn 	IR_Receiver;
	DigitalOut	IR_Emitter;
};

#endif 