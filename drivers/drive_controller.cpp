/**
 *
 */

#include "drive_controller.hpp"


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


// Go forward 1 cell
void forward() 
{
	float constSpeed = 0.2;
	int encoderLimit = 30000;

	leftMotor.go(constSpeed);
	rightMotor.go(constSpeed);

	//&stopMotors( leftMotor.stop(), rightMotor.stop());
	while(getEncoderDistance() < encoderLimit) { }

	leftMotor.stop();
	rightMotor.stop();
	resetEncoders();
}


void turnLeft()
{
	float constSpeed = 0.2;
	int encoderLimit = 14500;

	int leftRead = leftEncoder.read();
	int rightRead = rightEncoder.read();

	
	resetEncoders();
	leftMotor.go(-constSpeed);
	rightMotor.go(constSpeed);

	//&stopMotors( leftMotor.stop(), rightMotor.stop());
	while ((leftRead > -encoderLimit) && (rightRead < encoderLimit)) { 
		leftRead = leftEncoder.read();
		rightRead = rightEncoder.read();
	}

	leftMotor.stop();
	rightMotor.stop();
	 
	print_both_encoders('L', leftRead, rightRead);
	resetEncoders();
}


void turnRight()
{
	float constSpeed = 0.2;
	int encoderLimit = 14500;

	int leftRead = leftEncoder.read();
	int rightRead = rightEncoder.read();


	resetEncoders();
	leftMotor.go(constSpeed);
	rightMotor.go(-constSpeed);

	//&stopMotors( leftMotor.stop(), rightMotor.stop());
	//while ((leftEncoder.read() < encoderLimit) || (rightEncoder.read() > -encoderLimit)) { 
	while ((leftRead < encoderLimit) && (rightRead > -encoderLimit)) { 
		leftRead = leftEncoder.read();
		rightRead = rightEncoder.read();
	}

	leftMotor.stop();
	rightMotor.stop();
	
	print_both_encoders('R', leftRead, rightRead);
	resetEncoders();
}
