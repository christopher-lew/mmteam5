/**
 * Collection of functions that physically move the mouse from cell to cell.
 */

#include "drive_control.hpp"

/*
 * Takes in a float speed and a character that dictates the direction of the next move.
 * Designed to be implemented in main, where nextMove comes from maze.
 */
void moveFalcon(char nextMove, float speed)
{
	if (nextMove == 'F') {
		forward(speed);
	}
	else if (nextMove == 'R') {
		turnRight(speed);
		forward(speed);
	}
	else if (nextMove == 'L') {
		turnLeft(speed);
		forward(speed);
	}
	else {
		turnAround(speed);
		forward(speed);
	}
}

// Go forward 1 cell
void forward(float speed) 
{
	// TODO: float constSpeed = 0.3;
	//float speed = 0.2;
	//int CELL_DISTANCE = 28000; // TODO: implement as #define
	float fwd_speed = 0.12;
	int CELL_DISTANCE = 41000;
	bool alignToFront = false;

	pid.resetEncoders();
	leftMotor.instantAccel(fwd_speed);
	rightMotor.instantAccel(fwd_speed);

	while(pid.getEncoderDistance() < CELL_DISTANCE) {
		alignToFront = pid.keepStraight(); // use timer to execute every 1 ms
		if (alignToFront) {
			pid.alignToFrontWall();
			break;
		}
	}

	leftMotor.instantStop();
	rightMotor.instantStop();
}


void turnRight(float speed)
{
	float turnRight_speed = 0.16;
	int encLimit = 15700;

	leftMotor.instantStop();
	rightMotor.instantStop();
	wait_ms(MVMT_WAIT_MS);
	
	pid.resetEncoders();
	leftMotor.instantAccel(turnRight_speed);
	rightMotor.instantAccel(-turnRight_speed);

	while((leftEncoder.read() < encLimit) && (rightEncoder.read() > -encLimit)) {
		// TODO: pid.turn('R'); // use timer to ensure constant execution at every 1 ms
	}

	leftMotor.instantStop();
	rightMotor.instantStop();
	wait_ms(MVMT_WAIT_MS);
}


void turnLeft(float speed)
{
	float turnRight_speed = 0.16;
	int encLimit = 51000;

	leftMotor.instantStop();
	rightMotor.instantStop();
	wait_ms(MVMT_WAIT_MS);
	
	pid.resetEncoders();
	leftMotor.instantAccel(turnRight_speed);
	rightMotor.instantAccel(-turnRight_speed);

	while((leftEncoder.read() < encLimit) && (rightEncoder.read() > -encLimit)) {
		// TODO: pid.turn('L'); // use timer to ensure constant execution at every 1 ms
	}

	leftMotor.instantStop();
	rightMotor.instantStop();
	wait_ms(MVMT_WAIT_MS);
}


void turnAround(float speed)
{
	float turnRight_speed = 0.16;
	int encLimit = 34500;

	leftMotor.instantStop();
	rightMotor.instantStop();
	wait_ms(MVMT_WAIT_MS);
	
	pid.resetEncoders();
	leftMotor.instantAccel(turnRight_speed);
	rightMotor.instantAccel(-turnRight_speed);

	while((leftEncoder.read() < encLimit) && (rightEncoder.read() > -encLimit)) {
		// TODO: pid.turn('R'); // use timer to ensure constant execution at every 1 ms
	}

	leftMotor.instantStop();
	rightMotor.instantStop();
	wait_ms(MVMT_WAIT_MS);
}


/*
void turnLeft(float speed)  // TODO: USING "speed"
{
	float turnLeft_speed = 0.17;
	float turnLeft_angle = -70.0;

	ledRed = 1;
	ledYellow = 0;
	ledGreen = 0;
	leftMotor.stop();
	rightMotor.stop();
	wait_ms(100);

	pid.resetEncoders();
	gyro.start_sampling();
	leftMotor.accel(-turnLeft_speed);
	rightMotor.accel(turnLeft_speed);


	while(gyro.getAngle() > turnLeft_angle) {
		// TODO: pid.turn('L'); // use timer to execute every 1 ms
	}

	gyro.stop_sampling();
	leftMotor.stop();
	rightMotor.stop();
	wait_ms(100);
}


void turnRight(float speed) // TODO: USING "speed"
{
	float turnRight_speed = 0.2;
	float turnRight_angle = 70.0;

	ledRed = 0;
	ledYellow = 0;
	ledGreen = 1;
	leftMotor.stop();
	rightMotor.stop();
	wait_ms(100);
	
	pid.resetEncoders();
	gyro.start_sampling();
	leftMotor.accel(turnRight_speed);
	rightMotor.accel(-turnRight_speed);


	while(gyro.getAngle() < turnRight_angle) {
		// TODO: pid.turn('R'); // use timer to ensure constant execution at every 1 ms
	}

	gyro.stop_sampling();
	leftMotor.stop();
	rightMotor.stop();
	wait_ms(100);
}


void turnAround(float speed) // TODO: USING "speed"
{
	float turnRight_speed = 0.2;
	float turnRight_angle = 140.0;

	ledRed = 0;
	ledYellow = 0;
	ledGreen = 1;
	leftMotor.stop();
	rightMotor.stop();
	wait_ms(100);
	
	pid.resetEncoders();
	gyro.start_sampling();
	leftMotor.accel(turnRight_speed);
	rightMotor.accel(-turnRight_speed);


	while(gyro.getAngle() < turnRight_angle) {
		// TODO: pid.turn('R'); // use timer to ensure constant execution at every 1 ms
	}

	gyro.stop_sampling();
	leftMotor.stop();
	rightMotor.stop();
	wait_ms(100);
}
*/

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- 

char rightWallFollower()
{
	bool leftWall = leftIR.adjWall();
	bool frontLeftWall = frontLeftIR.adjWall();
	bool frontRightWall = frontRightIR.adjWall();
	bool rightWall = rightIR.adjWall();
		
	if ( !(rightWall) ) {
		ledRed = 0;
		ledYellow = 0;
		ledGreen = 1;
		return 'R';
	}

	else if ( !(frontLeftWall) && !(frontRightWall) ) {
		ledRed = 0;
		ledYellow = 1;
		ledGreen = 0;
		return 'F';
	}

	else if ( !(leftWall) ) {
		ledRed = 1;
		ledYellow = 0;
		ledGreen = 0;
		return 'L';
	}

	else {
		ledRed = 1;
		ledYellow = 1;
		ledGreen = 1;
		return 'A';
	}
}


char leftWallFollower()
{
	bool leftWall = leftIR.adjWall();
	bool frontLeftWall = frontLeftIR.adjWall();
	bool frontRightWall = frontRightIR.adjWall();
	bool rightWall = rightIR.adjWall();
		
	if ( !(leftWall) ) {
		ledRed = 1;
		ledYellow = 0;
		ledGreen = 0;
		return 'L';
	}	

	else if ( !(frontLeftWall) && !(frontRightWall) ) {
		ledRed = 0;
		ledYellow = 1;
		ledGreen = 0;
		return 'F';
	}

	else if ( !(rightWall) ) {
		ledRed = 0;
		ledYellow = 0;
		ledGreen = 1;
		return 'R';
	}

	else {
		ledRed = 1;
		ledYellow = 1;
		ledGreen = 1;
		return 'A';
	}
}