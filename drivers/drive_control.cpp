/**
 *
 */

#include "drive_control.hpp"

#define MVMT_WAIT_MS 250


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
	//float speed = 0.2;
	//int CELL_DISTANCE = 28000; // TODO: implement as #define
	float fwd_speed = 0.13;
	int CELL_DISTANCE = 36000;
	bool alignToFront = false;

	resetEncoders();
	leftMotor.accel(fwd_speed);
	rightMotor.accel(fwd_speed);

	while(getEncoderDistance() < CELL_DISTANCE) {
		wait_ms(1);
		alignToFront = PID_keepStraight(); // use timer to execute every 1 ms
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


void turnRight(float speed) // TODO: USING "speed"
{
	float turnRight_speed = 0.16;
	int encLimit = 15700;

	leftMotor.stop();
	rightMotor.stop();
	wait_ms(MVMT_WAIT_MS);
	
	resetEncoders();
	leftMotor.accel(turnRight_speed);
	rightMotor.accel(-turnRight_speed);

	while((leftEncoder.read() < encLimit) && (rightEncoder.read() > -encLimit)) {
		// TODO: PID_turn('R'); // use timer to ensure constant execution at every 1 ms
	}

	leftMotor.stop();
	rightMotor.stop();
	wait_ms(MVMT_WAIT_MS);
}

void turnLeft(float speed)
{
	float turnRight_speed = 0.16;
	int encLimit = 51000;

	leftMotor.stop();
	rightMotor.stop();
	wait_ms(MVMT_WAIT_MS);
	
	resetEncoders();
	leftMotor.accel(turnRight_speed);
	rightMotor.accel(-turnRight_speed);

	while((leftEncoder.read() < encLimit) && (rightEncoder.read() > -encLimit)) {
		// TODO: PID_turn('R'); // use timer to ensure constant execution at every 1 ms
	}

	leftMotor.stop();
	rightMotor.stop();
	wait_ms(MVMT_WAIT_MS);
}

void turnAround(float speed)
{
	float turnRight_speed = 0.16;
	int encLimit = 34500;

	leftMotor.stop();
	rightMotor.stop();
	wait_ms(MVMT_WAIT_MS);
	
	resetEncoders();
	leftMotor.accel(turnRight_speed);
	rightMotor.accel(-turnRight_speed);

	while((leftEncoder.read() < encLimit) && (rightEncoder.read() > -encLimit)) {
		// TODO: PID_turn('R'); // use timer to ensure constant execution at every 1 ms
	}

	leftMotor.stop();
	rightMotor.stop();
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
	float turnRight_angle = 70.0;

	ledRed = 0;
	ledYellow = 0;
	ledGreen = 1;
	leftMotor.stop();
	rightMotor.stop();
	wait_ms(100);
	
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
	float turnRight_speed = 0.2;
	float turnRight_angle = 140.0;

	ledRed = 0;
	ledYellow = 0;
	ledGreen = 1;
	leftMotor.stop();
	rightMotor.stop();
	wait_ms(100);
	
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
*/
// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- 

// ['F', 'R', 'L', 'A']
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