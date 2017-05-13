/**
 *
 */

#include "pid.hpp"

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
	
	else if (leftWall || rightWall) {
		PID_alignUsingSides(leftWall, rightWall);
	}
	
	else { 
		PID_HailMary();
	}

	return alignToFrontWall;
}


/* Use frontLeft & frontRight IRs to keep the motors straight */
void PID_alignToFrontWall()
{
	// TODO
}


/* Uses left and/or right walls to align the mouse */
void PID_alignUsingSides(bool leftWall, bool rightWall)
{	
	//#define PID_ALIGN_FRONT_DIST 3 // centimeters
	// Use both walls to align
	if (leftWall && rightWall) {
		// TODO
	}
	// Use only left wall to align
	else if (leftWall) {
		// TODO
	}
	// Use only right wall to align
	else {
		// TODO
	}
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