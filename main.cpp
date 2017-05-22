#include "config/initModes.hpp"


#if _OPERATING_MODE == 'M'

	#include "src/maze.h"
	#include <stdio.h>
	#include <iostream>
	#include <vector>
	#include <cstdlib>
	#include "mbed.h"
	#include "config/initDevices.hpp"
	#include "drivers/debug_io.hpp"
	#include "drivers/drive_control.hpp"
	#include "drivers/pid.hpp"
	#include "drivers/testFunctions.hpp"

	using namespace std;

	int main() {

		int state = 0 ;
		Maze();
		cycleLEDs(0.1);

		while (state == 0) { // Runnable State
			
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

	    while (state == 1) {
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

    while (state == 2) { // Go Home State
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

    while (state == 3) { // Speed Run State
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

	while (state == -1) {
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

// END





#elif _OPERATING_MODE == 'D'

	#include "mbed.h"
	#include "config/initDevices.hpp"
	#include "drivers/testFunctions.hpp"
	#include "drivers/debug_io.hpp"


	int main()
	{
		simpleDemo();
	}
// END





#elif _OPERATING_MODE == 'W'

	#include "mbed.h"
	#include "config/initDevices.hpp"
	#include "drivers/debug_io.hpp"
	#include "drivers/drive_control.hpp"
	#include "drivers/pid.hpp"
	#include "drivers/testFunctions.hpp"


	#define EXPLORING_SPEED 0.2
	#define _EXPLORING 1
	#define _RUNNING 2
	#define _RETURNING 3

	volatile int MOUSE_STATE = _EXPLORING;


	int main()
	{
		char nextMove;

		cycleLEDs(0.05);
		wait(3);
		cycleLEDs(0.05);
		
		int i = 0;
		int moves = 12;
		while (i < moves) {
			nextMove = rightWallFollower();
			moveFalcon(nextMove, EXPLORING_SPEED);
			i++;
		}

	}

// END




#elif _OPERATING_MODE == 'I'

	#include "mbed.h"
	#include "config/initConstants.hpp"
	#include "config/initDevices.hpp"
	#include "drivers/debug_io.hpp"
	#include "drivers/drive_control.hpp"
	#include "drivers/pid.hpp"
	#include "drivers/testFunctions.hpp"

	int main()
	{
		cycleLEDs(0.1);
		/*
		bluetooth.printf("Left:\r\n");
		IR_calibration(leftIR, IR_SIGDELAY, IR_SIGREST);
		bluetooth.printf("Right:\r\n");
		IR_calibration(rightIR, IR_SIGDELAY, IR_SIGREST);
		*/
		
		/*
		while(1) {
			bluetooth.printf("Left:\r\n");
			IR_calibration(leftIR, IR_SIGDELAY, IR_SIGREST);
			bluetooth.printf("Right:\r\n");
			IR_calibration(rightIR, IR_SIGDELAY, IR_SIGREST);
			wait(0.2);
		}
		*/
		
		/*
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
		*/

		//Gyro_calibration(150, 100);
		wait(2);
		bluetooth.printf("left Dist: %1.4f\r\n", leftIR.distToWall());
		bluetooth.printf("right Dist: %1.4f\r\n", rightIR.distToWall());
		//testBuzzer();
	}

// END





#elif _OPERATING_MODE == 'T'

	#include "mbed.h"
	#include "config/initDevices.hpp"
	#include "drivers/testFunctions.hpp"
	#include "drivers/debug_io.hpp"
	#include "drivers/drive_control.hpp"
	#include "devices/QEI_HW.hpp"

	int main()
	{	
		cycleLEDs(0.05);
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
		
		/*
		float gyroAvg = 0;
		float gyroRead = 0;

		cycleLEDs(0.05);
		gyro.start_sampling();

		for (int i = 0; i < 20; i++) {
			wait(0.2);
			gyroRead = gyro.getADCRead();
			gyroAvg += gyroRead;
			bluetooth.printf("Gyro:\r\nADC Read = %1.15f\r\n", gyroRead);
		}
		
		gyroAvg /= 20;
		bluetooth.printf("\r\nGyro Average = %1.15f\r\n", gyroAvg);
		*/
	}


#endif