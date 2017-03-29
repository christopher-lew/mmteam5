/**
 * Implementation of test functions.
 */

 #include "testFunctions.hpp"

void cycleLEDs()
{
	ledRed = 0;
	ledYellow = 0;
	ledGreen = 0;

	for(int i = 0; i < 3; i += 1 ) {
		ledRed = !ledRed;
		wait(0.5);

		ledRed = !ledRed;
		ledYellow = !ledYellow;
		wait(0.5);

		ledYellow = !ledYellow;
		ledGreen = !ledGreen;
		wait(0.5);

		ledGreen = !ledGreen;
	}
}

void cycleMFs()
{
	float a = 0.0;
	ledMf.period_ms(5);
	ledMf.write(a);

	for(int i = 1; i <= 5; i += 1) {
		a += 0.2;
		ledMf.write(a);
		wait(1.0);
	}

	ledMf.write(0);
}

void testBuzzer()
{
	float freq = 1.0/400.0;

	buzzer.period(freq);
	buzzer.write(0.5);
	
	wait(1.0);
	buzzer.write(0.25);

	wait(1.0);
	buzzer.write(0);
}