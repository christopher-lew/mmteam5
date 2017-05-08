/**
 * This file is pseudocode for how the mouse will navigate throught the maze. 
 * The extension is .cpp only because sublime will automatically format it nicely.
 */


#define EXPLORING_SPEED 0.3
#define RUN_SPEED 0.6

#define CELL_DISTANCE 15000

#define _EXPLORING 1
#define _RUNNING 2
#define _GO_HOME ???



volitile int MOUSE_STATE = _EXPLORING;


int main()
{
	// First state is always exploring
	while(MOUSE_STATE == _EXPLORING)
	{
		char nextMove = maze.getNextMove(); 	
		moveFalcon(nextMove, EXPLORING_SPEED);	
		maze.updatePosition(nextMove)	// Assume that the last movement was a success and update maze
	}

	// Once the maze has been solved, mouse will never be in _EXPLORING STATE AGAIN
	while(MOUSE_STATE == _RUNNING)
	{

	}

	// Possible need to have _GO_HOME state, or just combined _GO_HOME with _RUNNING
	// Need to figure out how to "soft" restart the mouse so that it can start a new trial run
	while(MOUSE_STATE == _GO_HOME)
	{

	}

	return 0;
}



// ELEMENTARY MOVEMENT FUNCTIONS (/drivers/drive_controller.cpp)
void moveFalcon(char nextMove, float speed)
{
	if (nextMove == 'F') {
		forward(speed);
	}
	else if (nextMove == 'R') {
		turnRight();
		forward(speed);
	}
	else if (nextMove == 'L') {
		turnLeft();
		forward(speed);
	}
	else {
		turnRight();
		turnRight();
		forward(speed);
	}
}


void forward(speed)
{
	resetEncoders();
	leftMotor.accel(speed);
	rightMotor.accel(speed);

	while(getEncoderDistance() < CELL_DISTANCE) {
		PID_keepStraight(); // use timer to execute every 1 ms
	}

	leftMotor.stop();
	rightMotor.stop();
}


void turnRight()
{
	float turnRight_speed = 0.2;
	float turnRight_angle = 85.0;

	gyro.reset();
	resetEncoders();
	leftMotor.accel(turnRight_speed);
	rightMotor.accel(-turnRight_speed);

	while(gyro.getAngle() < turnRight_angle) {
		PID_turn('R'); // use timer to ensure constant execution at every 1 ms
	}

	leftMotor.stop();
	rightMotor.stop();
}


void turnLeft()
{
	float turnLeft_speed = 0.2;
	float turnLeft_angle = -85.0;

	gyro.reset();
	resetEncoders();
	leftMotor.accel(-turnLeft_speed);
	rightMotor.accel(turnLeft_speed);

	while(gyro.getAngle() > turnLeft_angle) {
		PID_turn('L'); // use timer to execute every 1 ms
	}

	leftMotor.stop();
	rightMotor.stop();
}



// PID MONITORING FUNCTIONS (/drivers/PID.cpp)
// this function should adjust both motors to keep moving straight in a forward direction
void PID_keepStraight()
{
	// Boolean flags:
	int leftWall = 	 	leftIR.adjWall();
	int rightWall = 	rightIR.adjWall();
	int frontLeftWall =	frontLeftIR.adjWall();
	int frontRightWall=	frontRightIR.adjWall();

	if (frontLeftWall && frontLeftWall) {
		alignFront();
	}
	else if (leftWall || rightWall) {
		alignSides(leftWall, rightWall);
	}
	else { /* Hope for the best */ }
}

void alignFront()
{

}

void alignSides(int leftWall, int rightWall)
{

}


// this function should ensure that both motors are turning (and not that one is lagging behind)
void PID_turn(char direction)
{

}