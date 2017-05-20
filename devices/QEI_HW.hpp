/**
 * Quadrature Encoders implemented using hardware timer counters.
 */

#ifndef QEI_HW_H
#define QEI_HW_H

#include "mbed.h"

#define ENC_RESET_COUNT 1000000

void EncoderInitTIM2();
void EncoderInitTIM5();


class QEI_HW
{
public:
	QEI_HW(int TIM_choice);
	unsigned int read();
	void reset();

//private:
	int TIM_X;
};

#endif