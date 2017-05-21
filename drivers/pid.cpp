/**
 *
 */

#include "pid.hpp"

// Init all important PID variables & Constants
#define Kp 0.0
#define Kd 0.0

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


/* Use frontLeft & frontRight IRs to keep the motors straight */
void PID_alignToFrontWall()
{
	// TODO
	float right = frontRightIR.distToWall();
	while (right > PID_ALIGN_FRONT_DIST) {
		right = frontRightIR.distToWall();
	}

	leftMotor.stop();
	rightMotor.stop();
}


/* Uses left and/or right walls to align the mouse */
void PID_alignUsingSides(bool leftWall, bool rightWall)
{	
	//#define PID_ALIGN_FRONT_DIST 3 // centimeters
	// Use both walls to align
	if (leftWall && rightWall) {
		errorP = leftIR.distToWall() - rightIR.distToWall();
		errorD = errorP - oldErrorP;
	}

	// Use only left wall to align
	else if (leftWall) {
		//errorP = 2 * ()
		errorP = 0;
		errorD = 0;
	}

	// Use only right wall to align
	else if (rightWall) {
		errorP = 0;
		errorD = 0;
	}

	else {
		//PID_HailMary();
		errorP = 0;
		errorD = 0;
	}

	totalError = Kp*errorP + Kd*errorD;
	oldErrorP = errorP;

	leftMotor.accel(leftMotor.curSpeed - totalError);
	rightMotor.accel(rightMotor.curSpeed + totalError);
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