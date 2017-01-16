/**
 * This encoder class is dependent on using the "software" solution of using the mbed InterruptIn class
 * rather than using hardware interrupt pins.
 */

#ifndef ENCODER_H
#define ENCODER_H

#include "mbed.h"


class Encoder
{
public:
	volatile int count;
	
	Encoder(PinName channelA_pin, PinName channelB_pin);
	int read();
	void reset();

private:
	InterruptIn channelA;
	InterruptIn channelB;
	
	void countChange();
}

#endif