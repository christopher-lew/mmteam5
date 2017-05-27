/**
 * PID Controller for the Falcon.
 */

#include "pid.hpp"

// Init all important PID variables & Constants
//#define Kp 0.002
//#define Kd 0.008

//#define Kp 0.000203
//#define Kd 0.000315

//#define Kp 0.000075
//#define Kd 0.00055

#define Kp 0.000075
#define Kd 0.00055




PID_Controller::PID_Controller(void)
{
	this->errorP = 0;
	this->oldErrorP = 0;
	this->errorD = 0;
	this->totalError = 0;
}


/* This function should adjust both motors to keep moving straight in a forward direction */
bool PID_Controller::keepStraight()
{
	bool alignToFrontWall = false;
	// Boolean flags:
	bool leftWall = 	 	leftIR.adjWall();
	bool rightWall = 		rightIR.adjWall();
	bool frontLeftWall =	frontLeftIR.adjWall();
	bool frontRightWall=	frontRightIR.adjWall();

	if (frontLeftWall && frontRightWall) {
		alignToFrontWall = true;
	}
	
	else {
		this->alignUsingSides(leftWall, rightWall);
	}

	return alignToFrontWall;
}


/* Uses left and/or right walls to align the mouse */
void PID_Controller::alignUsingSides(bool leftWall, bool rightWall)
{	
	float leftError = 0;
	float rightError = 0;
	// Use both walls to align
	if (leftWall && rightWall) {
	errorP = leftIR.distToWall() - rightIR.distToWall() - PID_LtoR_OFFSET;
		errorD = errorP - oldErrorP;
	}

	// Use only left wall to align
	else if (leftWall) {
		errorP = 2 * (leftIR.distToWall() - PID_SIDE_ALIGN);
		errorD = errorP - oldErrorP;
	}

	// Use only right wall to align
	else if (rightWall) {
		errorP = 2 * (rightIR.distToWall() - PID_SIDE_ALIGN);
		errorD = errorP - oldErrorP;
	}

	else {
		//PID_HailMary();
		errorP = 0;
		errorD = 0;
	}

	totalError = Kp*errorP + Kd*errorD;
	oldErrorP = errorP;

	leftMotor.instantAccel(leftMotor.curSpeed - totalError);
	rightMotor.instantAccel(rightMotor.curSpeed + totalError);
}


/* Use frontLeft & frontRight IRs to keep the motors straight */
void PID_Controller::alignToFrontWall()
{
	leftMotor.instantStop();
	rightMotor.instantStop();
	cycleMFs(0.025);
	leftMotor.instantAccel(PID_DECCEL_SPEED);
	rightMotor.instantAccel(PID_DECCEL_SPEED);
	
	int fRightDist = frontRightIR.distToWall();
	int fLeftDist = frontLeftIR.distToWall();

	while ( (fRightDist > PID_FRONT_ALIGN) && (fLeftDist > PID_FRONT_ALIGN) ) {
		//PID_alignUsingSides(leftIR.adjWall(), rightIR.adjWall());
		fRightDist = frontRightIR.distToWall();
		fLeftDist = frontLeftIR.distToWall();
	}

	leftMotor.instantAccel(-0.05);
	rightMotor.instantAccel(-0.05);
	wait_ms(100);
	leftMotor.instantStop();
	rightMotor.instantStop();
}


/* Try and get a read 2 walls away or just match the encoder counts on L&R */
void PID_Controller::HailMary()
{
	// TODO
}


/* this function should ensure that both motors are turning (and not that one is lagging behind) */
void PID_Controller::turn(char direction)
{
	// TODO
}


/*
 * Test function turns the motor on to go forward for a set amount of time (not distance/encoder ticks)
 */
void PID_Controller::calibration(float _KP, float _KD, int samples, float sample_period, bool print_pidLog)
{
	float pid_log[samples][2];
	float left_log[samples];
	float right_log[samples];

	int print_args = 4;
	float speed = _EXPLORE_SPEED;
	
	bool leftWall;
	bool rightWall;
	float time_left;
	Timer pid_timer;

	// ----- Effectively the drive_control/forward() function -----
	this->resetEncoders();
	leftMotor.instantAccel(speed);
	rightMotor.instantAccel(speed);

	for(int i = 0; i < samples; i++) {
		pid_timer.reset();
		pid_timer.start();

		// ----- Effectively keepStraight() & alignUsingSides() -----
		leftWall = leftIR.adjWall();
		rightWall= rightIR.adjWall();

		left_log[i] = leftIR.distToWall();
		right_log[i] = rightIR.distToWall();
		
		if (leftWall && rightWall) {
			errorP = left_log[i] - right_log[i] - PID_LtoR_OFFSET;
			errorD = errorP - oldErrorP;
		totalError = _KP*errorP + _KD*errorD;
		oldErrorP = errorP;
		}
		else if (leftWall) {
			errorP = 2 * (left_log[i] - PID_SIDE_ALIGN);
			errorD = errorP - oldErrorP;
		totalError = _KP*errorP + _KD*errorD;
		oldErrorP = errorP;
		}
		else if (rightWall) {
			errorP = 2 * (right_log[i] - PID_SIDE_ALIGN);
			errorD = errorP - oldErrorP;
		totalError = -1*(_KP*errorP + _KD*errorD);
		oldErrorP = errorP;
		}
		else {
			errorP = 0;
			errorD = 0;
		}

		pid_log[i][0] = errorP;
		pid_log[i][1] = errorD;



		leftMotor.instantAccel(leftMotor.curSpeed - totalError);
		rightMotor.instantAccel(rightMotor.curSpeed + totalError);
		// ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

		time_left = sample_period - pid_timer.read();
		if (time_left >= 0) {
			wait(time_left);
		}
	}

	leftMotor.instantStop();
	rightMotor.instantStop();
	// ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

	// Print out CSV Data from pid_log
	bluetooth.printf("##### ##### #####\r\n");
	bluetooth.printf("Kp=%1.7f\r\nKd=%1.7f\r\n", _KP, _KD);
	bluetooth.printf("Samples=%d\r\nPeriod=%1.4f\r\nArgs=%d\r\n", samples, sample_period, print_args);
	if (print_pidLog) {
		for(int i = 0; i < samples; i++) {
			if (print_args == 4) {
				bluetooth.printf("%1.4f , %1.4f , %1.4f , %1.4f\r\n", pid_log[i][0], pid_log[i][1], left_log[i], right_log[i]);
			}
			else if (print_args == 2) {
				bluetooth.printf("%1.4f , %1.4f\r\n", pid_log[i][0], pid_log[i][1]);	
			}
		}
	}
}



// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- 
/*
 * Returns the average number of pulses across both encoders since last reset. 
 * Unit is encoder pulses; intended for straight driving only.
 */
int PID_Controller::getEncoderDistance()
{
	return (leftEncoder.read() + rightEncoder.read()) >> 1;
}


void PID_Controller::resetEncoders()
{
	leftEncoder.reset();
	rightEncoder.reset();
}