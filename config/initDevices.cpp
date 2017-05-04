#include "initDevices.hpp"

#if _FALCON_CONFIG == 21
	// Sensor Classes
	Buzzer buzzer(PB_15);
	
	IRPair leftIR(PB_0, PC_9);
	IRPair leftFrontIR(PC_5, PA_4);
	IRPair rightFrontIR(PC_4, PC_1);
	IRPair rightIR(PA_6, PC_14);
	IRPair testIR(PA_7, PH_0);
	
	Motor leftMotor(PB_5, PC_6);
	Motor rightMotor(PB_9, PB_8);
	
	Encoder leftEncoder(PB_10, PA_5);
	Encoder rightEncoder(PA_0, PA_1); 
	

	// LEDs
	PwmOut ledMf(PA_2);
	DigitalOut ledRed(PB_14);
	DigitalOut ledYellow(PB_13);
	DigitalOut ledGreen(PB_12);


	// Other IO Devices
	AnalogIn battery(PC_0);

	Serial pc(PC_10, PC_11);



#elif _FALCON_CONFIG == 20
	// Sensor Classes
	Buzzer buzzer(PA_2);
	
	IRPair leftIR(PC_3, PC_5);
	IRPair leftFrontIR(PC_1, PA_7);
	IRPair rightFrontIR(PC_0, PA_6);
	IRPair rightIR(PH_0, PA_4);

	Motor leftMotor(PC_8, PC_7);
	Motor rightMotor(PB_9, PB_8);
	/*
	Encoder leftEncoder(PB_3, PB_4);
	Encoder rightEncoder(PB_7, PB_6); 
	*/

	// LEDs
	//PwmOut ledMf(PC_6);
	DigitalOut ledMf(PC_6);
	DigitalOut ledRed(PB_15);
	DigitalOut ledYellow(PB_14);
	DigitalOut ledGreen(PB_13);


	// Other IO Devices
	AnalogIn battery(PA_3);

	Serial pc(PA_9, PA_10);

	DigitalIn userButton(PC_10);

#endif