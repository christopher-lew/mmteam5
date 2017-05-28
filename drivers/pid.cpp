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
	this->errorI = 0;
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
void PID_Controller::calibration(float _KP, float _KI, float _KD, int samples, float sample_period, bool print_pidLog, bool print_motors)
{
	float pid_log[samples][3];
	float left_dist[samples]; 	// if(print_motors): left_log = leftMotor.curSpeed, else: left_log = leftIR.distToWall()
	float right_dist[samples];
	float left_motor[samples];
	float right_motor[samples];

	int print_args = 5;
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

		left_dist[i] = leftIR.distToWall();
		right_dist[i] = rightIR.distToWall();
		
		if (leftWall && rightWall) {
			errorP = left_dist[i] - right_dist[i] - PID_LtoR_OFFSET;
			errorI += 0;//errorP;
			errorD = errorP - oldErrorP;
		}
		else if (leftWall) {
			errorP = 2 * (left_dist[i] - PID_SIDE_ALIGN);
			errorI += 0;//errorP;
			errorD = errorP - oldErrorP;
		}
		else if (rightWall) {
			errorP = 2 * (right_dist[i] - PID_SIDE_ALIGN);
			errorI += 0;//errorP;
			errorD = errorP - oldErrorP;
		}
		else {
			errorP = 0;
			errorI = 0;
			errorD = 0;
		}

		pid_log[i][0] = errorP;
		pid_log[i][1] = errorI;
		pid_log[i][2] = errorD;

		totalError = _KP*errorP + _KI*errorI + _KD*errorD;
		oldErrorP = errorP;

		leftMotor.instantAccel(leftMotor.curSpeed - totalError);
		rightMotor.instantAccel(rightMotor.curSpeed + totalError);

		left_motor[i] = leftMotor.curSpeed;
		right_motor[i] = rightMotor.curSpeed;
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
	bluetooth.printf("Kp=%.2f u\r\nKi=%.2f u\r\nKd=%.2f u\r\n", _KP*1000000, _KI*1000000, _KD*1000000);
	bluetooth.printf("Samples=%d\r\nPeriod=%1.4f\r\nArgs=%d\r\n", samples, sample_period, print_args);
	if (print_pidLog) {
		for(int i = 0; i < samples; i++) {
			if (print_args == 5) {
				if (print_motors) {
				bluetooth.printf("%1.4f , %1.4f , %1.4f , %1.4f , %1.4f\r\n", pid_log[i][0], pid_log[i][1], pid_log[i][2], left_motor[i], right_motor[i]);
				}
				else {
				bluetooth.printf("%1.4f , %1.4f , %1.4f , %1.4f , %1.4f\r\n", pid_log[i][0], pid_log[i][1], pid_log[i][2], left_log[i], right_log[i]);
				}
			}
			else if (print_args == 2) {
				bluetooth.printf("%1.4f , %1.4f , %1.4f\r\n", pid_log[i][0], pid_log[i][1], pid_log[i][2]);	
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