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
	float constSpeed = 0.3;
	int encoderLimit = 20000;

	leftMotor.accel(constSpeed);
	rightMotor.accel(constSpeed);

	//&stopMotors( leftMotor.stop(), rightMotor.stop());
	while(getEncoderDistance() < encoderLimit) { }

	leftMotor.stop();
	rightMotor.stop();
	resetEncoders();
}


void turnLeft()
{
	float constSpeed = 0.2;
	int encoderLimit = 17500;

	int leftRead;
	int rightRead;
	
	resetEncoders();
	leftRead = leftEncoder.read();
	rightRead = rightEncoder.read();
	
	leftMotor.accel(-constSpeed);
	rightMotor.accel(constSpeed);

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
	int encoderLimit = 17500;

	int leftRead;
	int rightRead;
	
	resetEncoders();
	leftRead = leftEncoder.read();
	rightRead = rightEncoder.read();
	
	leftMotor.accel(constSpeed);
	rightMotor.accel(-constSpeed);

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
