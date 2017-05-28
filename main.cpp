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
		int function_num = 7;
		bool isFront = true;

		cycleLEDs(0.1);


		while(1) {
		if (userButton)
		{
			cycleLEDs(0.05);
			
			// Raw ADC Values (Calibration for Front Sensors)
			if (function_num == 1) {
				for (int i = 0; i < 3; i++) {
					bluetooth.printf("----- ----- Trial %d ----- -----\r\n", i);
					int samples = 5;
					float left_avg = 0;
					float right_avg = 0;
					float left_log[samples];
					float right_log[samples];
					
					for (int i = 0; i < samples; i++) {
						left_log[i] = frontLeftIR.fireAndRead();
						right_log[i] = frontRightIR.fireAndRead();
						left_avg += left_log[i];
						right_avg += right_log[i];
					}
					
					left_avg /= samples;
					right_avg/= samples;
					
					bluetooth.printf("Front Left Avg = %1.4f\r\n", left_avg);
					for (int i = 0; i < samples; i++) {
						bluetooth.printf("%1.6f\r\n", left_log[i]);
					}
					
					bluetooth.printf("Front Right Avg = %1.4f\r\n", right_avg);
					for (int i = 0; i < samples; i++) {
						bluetooth.printf("%1.6f\r\n", right_log[i]);
					}
					bluetooth.printf("\r\n");
				}
			}


			// Quick Calibration of IRs
			else if (function_num == 2) {
				if (isFront) {
					//bluetooth.printf("Front Left:\r\n");
					//IR_calibration(frontLeftIR, IR_SIGDELAY, IR_SIGREST);
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
	
			
			// Calibrate single IR with loop
			else if (function_num == 3) {
				for (int i = 1; i < 10; i++) {
					bluetooth.printf("Front Right:\r\n");
					IR_calibration(frontRightIR, i, IR_SIGREST);
				}
			}
	
	
			// Get IR distances
			else if (function_num == 4) {
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
			else if (function_num == 5) {
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
	
	
			// Read Noise (No Emitter)
			else if (function_num == 6) {
				int samples = 1000;
				int wait_ms_time = 2;
				float noise_log[samples];
				
				wait(3);
				testBuzzer();
				
				for (int i = 0; i < samples; i++) {
					noise_log[i] = frontRightIR.readNoise();
					wait_ms(wait_ms_time);
				}
	
				bluetooth.printf("----- ----- NOISE READINGS ----- -----\r\n");
				for (int i = 0; i < samples; i++) {
					bluetooth.printf("%1.6f\r\n", noise_log[i]);
				}
				bluetooth.printf("\r\n");	
			}
	
	
			// HAIL MARY
			else if (function_num == 7) {
				int trials = 5;
				for (int i = 0; i < trials; i++) {
					bluetooth.printf("----- ----- ----- ----- ----- ----- ----- ----- ----- ----- Trial %d ----- ----- ----- ----- ----- ----- ----- ----- ----- -----\r\n", i);
					int samples = 5;
					float left_avg = 0;
					float right_avg = 0;
	
					float left_log[samples];
					float right_log[samples];
	
					float left_recv[samples][RECV_SAMPLES];
					float right_recv[samples][RECV_SAMPLES];
					
					for (int i = 0; i < samples; i++) {
						left_log[i] = frontLeftIR.fireAndRead();
						right_log[i] = frontRightIR.fireAndRead();
	
						left_avg += left_log[i];
						right_avg += right_log[i];
	
						left_recv[i][0] = frontLeftIR.recvLog[0];
						left_recv[i][1] = frontLeftIR.recvLog[1];
						left_recv[i][2] = frontLeftIR.recvLog[2];
						left_recv[i][3] = frontLeftIR.recvLog[3];
						left_recv[i][4] = frontLeftIR.recvLog[4];
	
						right_recv[i][0] = frontRightIR.recvLog[0];
						right_recv[i][1] = frontRightIR.recvLog[1];
						right_recv[i][2] = frontRightIR.recvLog[2];
						right_recv[i][3] = frontRightIR.recvLog[3];
						right_recv[i][4] = frontRightIR.recvLog[4];
					}
					
					left_avg /= samples;
					right_avg/= samples;
					
					bluetooth.printf("Front Left Avg = %1.4f\t\t\t\t\t\t\tFront Right Avg = %1.4f\r\n", left_avg, right_avg);
					for (int i = 0; i < samples; i++) {
						bluetooth.printf("%1.6f : (%1.6f, %1.6f, %1.6f, %1.6f, %1.6f)\t|\t%1.6f : (%1.6f, %1.6f, %1.6f, %1.6f, %1.6f)\r\n", left_log[i], left_recv[i][0], left_recv[i][1], left_recv[i][2], left_recv[i][3], left_recv[i][4], right_log[i], right_recv[i][0], right_recv[i][1], right_recv[i][2], right_recv[i][3], right_recv[i][4]);
					}
					bluetooth.printf("\r\n");
				}
			}
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
	        //getchar();
	        Maze::updateWalls(Maze::getMousey(), Maze::getMousex());
	        update_distances(Maze::getMousey(), Maze::getMousex());
	        //next_move(Maze::getMousey(), Maze::getMousex());
	        char next = next_move(Maze::getMousey(), Maze::getMousex()); 
	        moveFalcon(next, 0.2);
	        //print_maze();
		}

	    while (state == _GO_HOME) { // Go Home State
	        if (is_start(encodeCellIndex(Maze::getMousey(), Maze::getMousex()))) {
	            //print_maze();
	            //getchar();
	            // Do prep for Speed Run
	            speedRunPrep();
	            floodfill();
	            //print_maze();
	            state++;
	            continue;
	        }
	        //getchar();
	        cycleMFs(0.02);
	        Maze::updateWalls(Maze::getMousey(), Maze::getMousex());
	        update_distances(Maze::getMousey(), Maze::getMousex());
	        //next_move(Maze::getMousey(), Maze::getMousex());
	        char next = next_move(Maze::getMousey(), Maze::getMousex());
	        moveFalcon(next, 0.2);
	        //print_maze();

	    }

	    while (state == _SPEED_RUN) { // Speed Run State
			wait(3);
	        //getchar();
	        if (is_center(encodeCellIndex(Maze::getMousey(), Maze::getMousex()))) {
	            printf("suck it\n");
	            break;
	        }
	        cycleMFs(0.02);
	        Maze::updateWalls(Maze::getMousey(), Maze::getMousex());
	        //update_distances(Maze::getMousey(), Maze::getMousex());
	        // next_move(Maze::getMousey(), Maze::getMousex());
	        char next = next_move(Maze::getMousey(), Maze::getMousex()); 
	        moveFalcon(next, 0.2);
	        //print_maze();

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
		float _KD = 0.0000;
		
		float _KP_step = 0.00001;
		float _KD_step = 0.00000;

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