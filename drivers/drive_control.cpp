/**
 *
 */

#include "drive_control.hpp"


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


// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- 
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
	int CELL_DISTANCE = 28000; // TODO: implement as #define
	bool alignToFront = false;

	resetEncoders();
	leftMotor.accel(speed);
	rightMotor.accel(speed);


	while(getEncoderDistance() < CELL_DISTANCE) {
		wait_ms(10);
		//alignToFront = PID_keepStraight(); // use timer to execute every 1 ms
		if (alignToFront) {
			//break;
		}
	}

	if (alignToFront) {
		//PID_alignToFrontWall();
	}

	leftMotor.stop();
	rightMotor.stop();
}


void turnLeft(float speed)  // TODO: USING "speed"
{
	float turnLeft_speed = 0.17;
	float turnLeft_angle = -65.0;


	resetEncoders();
	gyro.start_sampling();
	leftMotor.accel(-turnLeft_speed);
	rightMotor.accel(turnLeft_speed);


	while(gyro.getAngle() > turnLeft_angle) {
		// TODO: PID_turn('L'); // use timer to execute every 1 ms
	}

	gyro.stop_sampling();
	leftMotor.stop();
	rightMotor.stop();
	wait_ms(100);
}


void turnRight(float speed) // TODO: USING "speed"
{
	float turnRight_speed = 0.2;
	float turnRight_angle = 75.0;
	
	
	resetEncoders();
	gyro.start_sampling();
	leftMotor.accel(turnRight_speed);
	rightMotor.accel(-turnRight_speed);


	while(gyro.getAngle() < turnRight_angle) {
		// TODO: PID_turn('R'); // use timer to ensure constant execution at every 1 ms
	}

	gyro.stop_sampling();
	leftMotor.stop();
	rightMotor.stop();
	wait_ms(100);
}


void turnAround(float speed) // TODO: USING "speed"
{
	float turnAround_speed = 0.2;
	float turnAround_angle = 170.0;
	
	
	resetEncoders();
	gyro.start_sampling();
	leftMotor.accel(turnAround_speed);
	rightMotor.accel(-turnAround_speed);


	while(gyro.getAngle() < turnAround_angle) {
		// TODO: PID_turn('R'); // use timer to ensure constant execution at every 1 ms
	}

	gyro.stop_sampling();
	leftMotor.stop();
	rightMotor.stop();
	wait_ms(100);
}

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- 

// ['F', 'R', 'L', 'A']
char rightWallFollower()
{
	if ( !(rightIR.adjWall()) ) {
		ledRed = 0;
		ledYellow = 0;
		ledGreen = 1;
		return 'R';
	}

	else if ( !(frontRightIR.adjWall()) ) {
		ledRed = 0;
		ledYellow = 1;
		ledGreen = 0;
		return 'F';
	}

	else if ( !(leftIR.adjWall()) ) {
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