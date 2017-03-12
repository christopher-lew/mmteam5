#include "mbed.h"
#include "./config/initDevices.hpp"
//#include "maze.h"

//#include <iostream> // Use pc instead of std?
//#include "debug_io.hpp" // Uncomment if debugging

int main()
{
	ledGreen = 1;
	wait(0.5);
	ledYellow = 1;
	wait(0.5);
	ledRed = 1;
	wait(0.5);
	
	buzzer.levelComplete();
	/*
	leftMotor.go(1);
	rightMotor.go(1);
	wait(1);
	leftMotor.stop();
	rightMotor.stop();
	*/
	return 0;
}
