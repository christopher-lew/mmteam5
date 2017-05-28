// Include all the config & driver files needed to run anything on the mouse
#include "mbed.h"
#include "config/initModes.hpp"
#include "config/initConstants.hpp"
#include "config/initDevices.hpp"
#include "drivers/debug_io.hpp"
#include "drivers/drive_control.hpp"
#include "drivers/pid.hpp"
#include "drivers/testFunctions.hpp"

PID_Controller pid;

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- 

#if _OPERATING_MODE == 'D'

	int main()
	{
		simpleDemo();
	}

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- 

#elif _OPERATING_MODE == 'G'

	int main() 
	{
		int function_num = 1;

		cycleLEDs(0.1);
		

		// Gyro calibration
		if (function_num == 1) {
			Gyro_calibration(150, 100);
		}


		// Get Gyro's raw ADC readings and print them out
		else if (function_num == 2) {
			int samples = 20;
			float wait_time = 0.2;

			float gyroAvg = 0;
			float gyroRead = 0;

			cycleLEDs(0.05);
			gyro.start_sampling();

			for (int i = 0; i < samples; i++) {
				wait(wait_time);
				gyroRead = gyro.getADCRead();
				gyroAvg += gyroRead;
				bluetooth.printf("Gyro:\r\nADC Read = %1.15f\r\n", gyroRead);
			}
			
			gyro.stop_sampling();
			gyroAvg /= 20;
			bluetooth.printf("\r\nGyro Average = %1.15f\r\n", gyroAvg);
		}


		testBuzzer();
	}

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- 

#elif _OPERATING_MODE == 'I'

	int main()
	{
		int function_num = 2;
		bool isFront = false;

		cycleLEDs(0.1);


		// Calibrate IRs
		if (function_num == 1) {
			if (isFront) {
				bluetooth.printf("Front Left:\r\n");
				IR_calibration(frontLeftIR, IR_SIGDELAY, IR_SIGREST);
				bluetooth.printf("Front Right:\r\n");
				IR_calibration(frontRightIR, IR_SIGDELAY, IR_SIGREST);
			}

			else {
				bluetooth.printf("Left:\r\n");
				IR_calibration(leftIR, IR_SIGDELAY, IR_SIGREST);
				bluetooth.printf("Right:\r\n");
				IR_calibration(rightIR, IR_SIGDELAY, IR_SIGREST);
			}
		}


		// Get IR distances
		else if (function_num == 2) {
			if (isFront) {
				bluetooth.printf("Front Left Dist: %1.4f\r\n", leftIR.distToWall());
				bluetooth.printf("Front Right Dist: %1.4f\r\n", rightIR.distToWall());
			}

			else {
				bluetooth.printf("Left Dist: %1.4f\r\n", leftIR.distToWall());
				bluetooth.printf("Right Dist: %1.4f\r\n", rightIR.distToWall());
			}
		}
		

		// Check adjWall states && print distances to all walls
		else if (function_num == 3) {
			bool frontLeftWall;
			bool frontRightWall;
			bool rightWall;
			bool leftWall;

			while(1) {
				frontLeftWall = frontLeftIR.adjWall();
				frontRightWall = frontRightIR.adjWall();
				rightWall = rightIR.adjWall();
				leftWall = leftIR.adjWall();

				ledRed = 0;
				ledYellow = 0;
				ledGreen = 0;

				if (frontLeftWall && frontRightWall) {
					ledYellow = 1;
				}
				if (leftWall) {
					ledRed = 1;
				}
				if (rightWall) {
					ledGreen = 1;
				}
				
				bluetooth.printf("Left Dist: %1.4f\r\n", leftIR.distToWall());
				bluetooth.printf("Front Left Dist: %1.4f\r\n", frontLeftIR.distToWall());
				bluetooth.printf("Front Right Dist: %1.4f\r\n\n", frontRightIR.distToWall());
				bluetooth.printf("right Dist: %1.4f\r\n", rightIR.distToWall());
			
				wait_ms(100);
			}
		}


		testBuzzer();
	}

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- 

#elif _OPERATING_MODE == 'M'

	#include "src/maze.h"
	#include <stdio.h>
	#include <iostream>
	#include <vector>
	#include <cstdlib>

	using namespace std;

	/** 
	 * _OPERATOR_INPUT = 0
	 * _EXPLORING = 1
	 * _GO_HOME = 2
	 * _SPEED_RUN = 3
	 * _WALL_FOLLOWER = -1
	 */

	int main() {

		int state = _OPERATOR_INPUT;
		Maze();
        Maze::initMaze();
		cycleLEDs(0.1);

		while (state == _OPERATOR_INPUT) { // Runnable State
			
			if (frontLeftIR.adjWall() && frontRightIR.adjWall()){
				cycleLEDs(0.1);
				cycleMFs(0.02);
				testBuzzer();

				state++;
				wait(1);
			}
			else if (userButton) {
				cycleMFs(0.05);
				state = -1;
				wait(3);
			}
		}

	    while (state == _EXPLORING) {
	        if (is_center(encodeCellIndex(Maze::getMousey(), Maze::getMousex()))) {
	            testBuzzer();
	            Maze::setStartAsGoal();
	            state++;
	            continue;
	        }
	        Maze::updateWalls(Maze::getMousey(), Maze::getMousex());
	        update_distances(Maze::getMousey(), Maze::getMousex());
	        char next = next_move(Maze::getMousey(), Maze::getMousex());
	        moveFalcon(next, 0.2);
		}

	    while (state == _GO_HOME) { // Go Home State
	        if (is_start(encodeCellIndex(Maze::getMousey(), Maze::getMousex()))) {
	            // Do prep for Speed Run
	            speedRunPrep();
	            floodfill();
	            state++;
	            continue;
	        }
	        cycleMFs(0.02);
	        Maze::updateWalls(Maze::getMousey(), Maze::getMousex());
	        update_distances(Maze::getMousey(), Maze::getMousex());
	        char next = next_move(Maze::getMousey(), Maze::getMousex());
	        moveFalcon(next, 0.2);

	    }

	    while (state == _SPEED_RUN) { // Speed Run State
			wait(3);
	        if (is_center(encodeCellIndex(Maze::getMousey(), Maze::getMousex()))) {
                printf("\nEndOfMaze\n");
	            break;
	        }

	        cycleMFs(0.02);

            std::vector<char> path;
            while (!is_center(encodeCellIndex(Maze::getMousey(), Maze::getMousex()))) {
                path.push_back(next_move(Maze::getMousey(), Maze::getMousex()));
            }

            print_maze();
            for (std::vector<char>::const_iterator i = path.begin(); i != path.end(); ++i) {
                std::cout << *i;
                moveFalcon(*i, 0.2);
            }

	    }

		while (state == _WALL_FOLLOWER) {
	    	char nextMove;
	    	//srand((unsigned) time(NULL));
	    	int randomNum = (rand()) % 10;
	    	cycleLEDs(0.05);
	    	if (randomNum < 2) {
	    		nextMove = leftWallFollower();
	    	}
	    	else {
				nextMove = rightWallFollower();
			}
			moveFalcon(nextMove, 0.2);
	    }
		
	    testBuzzer();
	}

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- 

#elif _OPERATING_MODE == 'P'

	int main()
	{
		bluetooth.baud(BAUD_RATE);
		
		//_KP = 0.000065;
		//_KD = 0.000250;

		int trial = 0;
		int n_trials = 4;
		bool waiting = true;

		int samples = 600;
		float sample_period = 0.002;	
			
		float _KP = 0.000020;
		float _KD = 0.000001;
		
		//float _KP = 0.0000125;
		//float _KD = 0.0000016;
		
		float _KP_step = 0.000005;
		float _KD_step = 0.0000005;

		cycleMFs(0.10);

		while (trial < n_trials) {
			while (waiting) {
				if (userButton) {
					cycleMFs(0.05);
					wait(1.5);
					
					pid.calibration(_KP, _KD, samples, sample_period, false);
					
					cycleLEDs(0.05);
					testBuzzer();
					waiting = false;
				}
			}
			
			waiting = true;
			trial++;
			_KP += _KP_step;
			_KD += _KD_step;
		}
		
		buzzer.levelComplete();
	}

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- 

#elif _OPERATING_MODE == 'T'

	#include "devices/QEI_HW.hpp"

	int main()
	{	
		cycleLEDs(0.05);
		/*
		QEI_HW rightEncoder(5);
		cycleMFs(0.05);
		int encRead = 0;
		
		bluetooth.printf("\r\nTimer choice = TIM_%d\r\n", rightEncoder.TIM_X);
		for (int i = 0; i < 20; i++) {
			encRead = rightEncoder.read();
			bluetooth.printf("Right Encoder = %d\r\n", encRead);
			rightEncoder.reset();
			wait(0.2);
		}
		*/

		for (int i = 0; i < 10; i++) {
			pid.keepStraight();
			wait(0.5);
		}
	}

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- 

#elif _OPERATING_MODE == 'W'

	int main()
	{
		char nextMove;
		int i = 0;
		int moves = 12;

		cycleLEDs(0.05);
		
		// Wait for user input
		while (1) {	
			if (frontLeftIR.adjWall() && frontRightIR.adjWall()){
				cycleLEDs(0.1);
				cycleMFs(0.02);
				testBuzzer();
				
				wait(1);
				break;
			}
		}
		
		while (i < moves) {
			nextMove = rightWallFollower();
			moveFalcon(nextMove, _EXPLORE_SPEED);
			i++;
		}

		testBuzzer();
	}


#endif