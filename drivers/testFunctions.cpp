/**
 * Implementation of test functions used to validate that all devices 
 * on the mouse are working as expected.
 */

#include "testFunctions.hpp"


void cycleLEDs(float flashPeriod)
{
	ledRed = 0;
	ledYellow = 0;
	ledGreen = 0;

	for(int i = 0; i < 3; i += 1 ) {
		ledRed = !ledRed;
		wait(flashPeriod);

		ledRed = !ledRed;
		ledYellow = !ledYellow;
		wait(flashPeriod);

		ledYellow = !ledYellow;
		ledGreen = !ledGreen;
		wait(flashPeriod);

		ledGreen = !ledGreen;
	}
}


void cycleMFs(float flashPeriod)
{
	float a = 0.0;
	ledMf.period_ms(5);
	ledMf.write(a);

	for(int i = 1; i <= 5; i += 1) {
		a += 0.2;
		ledMf.write(a);
		wait(flashPeriod);
	}

	ledMf.write(0);
}


void testBuzzer()
{
	buzzer.testSound();
	//wait(0.1);
	//buzzer.levelComplete();
	//buzzer.imperialMarch();
}


// +speed == Forward
void testMotors_straight(float speed, int duration_ms)
{
	leftMotor.accel(speed);
	rightMotor.accel(speed);
	
	wait_ms(duration_ms);
	
	leftMotor.stop();
	rightMotor.stop();
}


// +speed = CW rotation
void testMotors_rotate(float speed, int duration_ms)
{
	leftMotor.accel(speed);
	rightMotor.accel(-speed);
	
	wait_ms(duration_ms);
	
	leftMotor.stop();
	rightMotor.stop();
}


void simpleDemo() 
{
	cycleLEDs(0.1);
	buzzer.testSound();
	print_battery();
	
	
	testMotors_straight(0.2, 200);
	wait_ms(250);
	testMotors_straight(-0.2, 200);
	
	wait_ms(500);
	
	testMotors_rotate(0.25, 250);
	wait_ms(250);
	testMotors_rotate(-0.25, 250);
	
	wait_ms(250);
	buzzer.levelComplete();
	cycleMFs(0.2);
}



void ticker_switch1() {
	ledRed = !ledRed;
}
void ticker_switch2() {
	ledGreen = !ledGreen;
}

void tickerExample() 
{
	Ticker tick1;
	Ticker tick2;

	ledRed = 0;
	ledGreen = 0;

	tick1.attach(&ticker_switch1, 0.2);
	tick2.attach(&ticker_switch2, 1.0);

	wait(5);
	tick1.detach();
	ledRed = 0;
	
	wait(5);
	tick2.detach();		
	ledGreen = 0;
}

// ----- ----- ----- ----- SENSOR CALIBRATION ----- ----- ----- ----- ----- ----- ----- 

/*
 * Fires a burst of IR on/off cycles given the
 * 		ir
 * 		signal delay time (between turning on Emitter and reading Receiver)
 *		signal rest time (how much time we need to turn off the Emitter to allow firing capacitor to recharge)
 */
void IR_calibration(IRPair ir, int signal_delay_us, int signal_rest_us)
{
	int numBursts = 3;
	float avgBurstRead = 0.0;
	
	bluetooth.printf("********** %d us **********\r\n", signal_delay_us);

	for (int i = 0; i < numBursts; i++) {
		float avgDist = ir.calibration(signal_delay_us, signal_rest_us);
		float avgRead = 0.0;
		
		//bluetooth.printf("Avg Dist To Wall = %3.6f\r\n", avgDist);
		for (int i = 0; i < IR_SAMPLES; i++) {
			avgRead += ir.readLog[i];
			bluetooth.printf("%3.6f\r\n", ir.readLog[i]);
		}

		avgRead /= IR_SAMPLES;
		bluetooth.printf("Avg ADC Read = %3.6f\r\n", avgRead);
		
		avgBurstRead += avgRead;
		testBuzzer();
	}
	
	avgBurstRead /= numBursts;
	bluetooth.printf("Average burst read = %3.4f\r\n\n", avgBurstRead);
}



void Gyro_calibration(int num_samples, int sample_freq)
{
	Timer gyroTimer;
	float gyroAvg = 0.0;
	float gyroLog[num_samples];
	float sample_period = 1.0 / sample_freq;

	gyro.start_sampling();
	gyroTimer.start();
	for (int i = 0; i < num_samples; i++) {
		gyroTimer.reset();
		gyroLog[i] = gyro.getADCRead();
		while(gyroTimer.read() < sample_period) {}
	}
	gyro.stop_sampling();

	// Print out the information
	bluetooth.printf("Gyro Calibration Readings @ %d Hz\r\n", sample_freq);
	for (int i = 0; i < num_samples; i++) {
		gyroAvg += gyroLog[i];
		bluetooth.printf("%1.6f\r\n", gyroLog[i]);
	}
	gyroAvg /= num_samples;
	bluetooth.printf("Average = %1.4f\r\n\n", gyroAvg);
}