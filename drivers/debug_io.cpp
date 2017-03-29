/**
 * Implementation of debug_io functions.
 */

#include "debug_io.hpp"

void print_battery() 
{
	float Vbat = battery.read();
	pc.print("Battery: %1.2f (%1.2f V)\r\n", Vbat, Vbat*VOLT_CONV);
}

void print_ir(IRPair ir) 
{
	for (int i = 0; i < IR_SAMPLES; i++) {
		pc.printf("%3.9f\r\n", ir.readLog[i]);
	}
}