// DECLARE FALCON CONFIG VERSION (F20, F21, F22)
#define F20


#include "mbed.h"

#ifdef F20
	//PwmOut ledMf(PC_6);
	DigitalOut ledMf(PC_6);
	DigitalOut ledRed(PB_15);
	DigitalOut ledYellow(PB_14);
	DigitalOut ledGreen(PB_13);
	
	Buzzer buzzer(PA_2);
#endif

#ifdef F21
	//PwmOut ledMf(PA_2);
	DigitalOut ledMf(PA_2);
	DigitalOut ledRed(PB_14);
	DigitalOut ledYellow(PB_13);
	DigitalOut ledGreen(PB_12);
	
	Buzzer buzzer(PB_15);
#endif

int main()
{
	ledRed = 1;
	wait(0.5);
	ledYellow = 1;
	wait(0.5);
	ledGreen = 1;
	wait(0.5);
	
	buzzer.levelComplete();
	return 0;
}
