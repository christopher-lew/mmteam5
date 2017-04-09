/**
 * Implementation of debug_io functions.
 */

#include "debug_io.hpp"

extern Serial pc;
extern AnalogIn battery;

void print_battery() 
{
	float Vbat = battery.read();
	pc.printf("Battery: %1.4f (%1.4f V)\r\n", Vbat, Vbat*VOLT_CONV);
}

void print_ir(IRPair ir) 
{
	float dist = ir.distToWall();
	for (int i = 0; i < IR_SAMPLES; i++) {
		pc.printf("%3.9f\r\n", ir.readLog[i]);
	}
	pc.printf("Avg Dist To Wall = %3.9f\r\n\n", dist);
}