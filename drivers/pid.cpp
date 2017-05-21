/**
 *
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

volatile float errorP = 0;
volatile float oldErrorP = 0;
volatile float errorD = 0;
volatile float totalError = 0;


/* This function should adjust both motors to keep moving straight in a forward direction */
bool PID_keepStraight()
{
	bool alignToFrontWall = false;
	// Boolean flags:
	bool leftWall = 	 	leftIR.adjWall();
	bool rightWall = 		rightIR.adjWall();
	bool frontLeftWall =	frontLeftIR.adjWall();
	bool frontRightWall=	frontRightIR.adjWall();

	if (frontLeftWall && frontLeftWall) {
		alignToFrontWall = true;
	}
	
	else {
		PID_alignUsingSides(leftWall, rightWall);
	}

	return alignToFrontWall;
}


/* Uses left and/or right walls to align the mouse */
void PID_alignUsingSides(bool leftWall, bool rightWall)
{	
	float leftError = 0;
	float rightError = 0;
	// Use both walls to align
	if (leftWall && rightWall) {
		leftError = leftIR.distToWall() - PID_LEFT_ALIGN;
		rightError = rightIR.distToWall() - PID_RIGHT_ALIGN;
		
		errorP = leftError - rightError;
		errorD = errorP - oldErrorP;
	}

	// Use only left wall to align
	else if (leftWall) {
		errorP = 2 * (leftIR.distToWall() - PID_LEFT_ALIGN);
		errorD = errorP - oldErrorP;
	}

	// Use only right wall to align
	else if (rightWall) {
		errorP = 2 * (rightIR.distToWall() - PID_RIGHT_ALIGN);
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
void PID_alignToFrontWall()
{
	leftMotor.instantAccel(0);
	rightMotor.instantAccel(0);
	cycleMFs(0.025);
	
	leftMotor.instantAccel(COAST_SPEED);
	rightMotor.instantAccel(COAST_SPEED);
	
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
	leftMotor.instantAccel(0);
	rightMotor.instantAccel(0);
}


/* Try and get a read 2 walls away or just match the encoder counts on L&R */
void PID_HailMary()
{
	// TODO
}


/* this function should ensure that both motors are turning (and not that one is lagging behind) */
void PID_turn(char direction)
{
	// TODO
}



// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- 
/* Returns the average number of pulses across both encoders since last reset. Unit is encoder pulses; intended for straight driving only. */
int getEncoderDistance()
{
	return (leftEncoder.read() + rightEncoder.read()) >> 1;
}


void resetEncoders()
{
	leftEncoder.reset();
	rightEncoder.reset();
}