/**
 * "Software" encoder class implementation.
 */

#include "encoder.hpp"


/* Constructor */
Encoder::Encoder(PinName channelA_pin, PinName channelB_pin)
	: channelA(channelA_pin), channelB(channelB_pin)
{
	this->count = 0;
}