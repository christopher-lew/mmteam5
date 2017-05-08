/**
 * Implementation of debug_io functions.
 */

#include "debug_io.hpp"

extern Serial bluetooth;
extern AnalogIn battery;


void print_battery() 
{
	float Vbat1 = battery.read();
	wait_ms(1);
	float Vbat2 = battery.read();
	wait_ms(1);
	float Vbat3 = battery.read();
	bluetooth.printf("Battery: %1.4f (%1.4f V)\r\n", Vbat1, Vbat1*VOLT_CONV);
	bluetooth.printf("Battery: %1.4f (%1.4f V)\r\n", Vbat2, Vbat2*VOLT_CONV);
	bluetooth.printf("Battery: %1.4f (%1.4f V)\r\n\n", Vbat3, Vbat3*VOLT_CONV);
}


void print_ir(IRPair ir) 
{
	float dist = ir.distToWall();
	for (int i = 0; i < IR_SAMPLES; i++) {
		bluetooth.printf("%3.9f\r\n", ir.readLog[i]);
	}
	bluetooth.printf("Avg Dist To Wall = %3.9f\r\n\n", dist);
}


void print_encoder(char encChoice)
{
	int encCount;
	if (encChoice == 'L') { encCount = leftEncoder.read(); }
	else { encCount = rightEncoder.read(); }
	
	bluetooth.printf("%c_Encoder count = %d\r\n", encChoice, encCount);
}


void print_both_encoders(char turnDirection, int leftRead, int rightRead)
{
	if (turnDirection == 'L') {
		bluetooth.printf("Turning Left:\r\n");
	}
	else if (turnDirection == 'R') {
		bluetooth.printf("Turning Right:\r\n");
	}
	else { // No direction
		bluetooth.printf("Encoder Readings:\r\n");
	}

	bluetooth.printf("Left:  Read = %d \tCount = %d\r\n", leftRead, leftEncoder.read());
	bluetooth.printf("Right: Read = %d \tCount = %d\r\n", rightRead, rightEncoder.read());
	bluetooth.printf("\r\n");
}


void print_gyro()
{
	float gyroRead = gyro.read();
	bluetooth.printf("Gyro read = %1.9f\r\n", gyroRead);
}