#include "initDevices.hpp"

#if _FALCON_CONFIG == 21
	// Sensor Classes
	Buzzer buzzer(PB_15);
	
	IRPair leftIR(PB_0, PC_9, false);
	IRPair frontLeftIR(PC_5, PA_4, true);
	IRPair frontRightIR(PC_4, PC_1, true);
	IRPair rightIR(PA_6, PC_14, false);
	//IRPair testIR(PA_7, PH_0, false);
	
	Motor leftMotor(PB_5, PC_6);
	Motor rightMotor(PB_9, PB_8);
	
	Encoder leftEncoder(PB_10, PA_5);
	Encoder rightEncoder(PA_0, PA_1); 

	Gyro gyro(PB_1);
	

	// LEDs
	PwmOut ledMf(PA_2);
	DigitalOut ledRed(PB_14);
	DigitalOut ledYellow(PB_13);
	DigitalOut ledGreen(PB_12);


	// Other IO Devices
	AnalogIn battery(PC_0);

	Serial bluetooth(PC_10, PC_11);

	DigitalIn userButton(PH_0);



#elif _FALCON_CONFIG == 20
	// Sensor Classes
	Buzzer buzzer(PA_2);
	
	IRPair leftIR(PC_3, PC_5, false);
	IRPair frontLeftIR(PC_1, PA_7, true);
	IRPair frontRightIR(PC_0, PA_6, true);
	IRPair rightIR(PH_0, PA_4, false);

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

	Serial bluetooth(PA_9, PA_10);

	DigitalIn userButton(PC_10);

#endif