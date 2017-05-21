#include "config/initModes.hpp"


#if _OPERATING_MODE == 'M'

	#include "src/maze.h"
	#include <stdio.h>
	#include <iostream>
	#include <vector>
	#include "mbed.h"
	#include "config/initDevices.hpp"
	#include "drivers/debug_io.hpp"
	#include "drivers/drive_control.hpp"
	#include "drivers/pid.hpp"
	#include "drivers/testFunctions.hpp"

	using namespace std;

	int main() {
		int x = 0 ;
		Maze();
		cycleLEDs(0.1);
		wait(3);
		cycleLEDs(0.1);

		bool stop = false;
		
		while (1) {
			if(!stop && is_center(encodeCellIndex(Maze::getMousey(), Maze::getMousex()))) {
               Maze::setStartAsGoal();
               stop = true;

       }
       // 		if (!goaway && stop && is_start(encodeCellIndex(Maze::getMousey(), Maze::getMousex()))) {
       //      Maze::speedRunPrep();
       //      goaway = true;
       // }
	        cycleMFs(0.02);
	        Maze::updateWalls(Maze::getMousey(), Maze::getMousex());
	        update_distances();
	        char next = next_move(Maze::getMousey(), Maze::getMousex());
	        moveFalcon(next, 0.2);
	        
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

		cycleLEDs(0.1);
		wait(2);
		cycleLEDs(0.1);

		/*while (MOUSE_STATE == _EXPLORING)
		{
			nextMove = rightWallFollower();
			moveFalcon(nextMove, EXPLORING_SPEED);
		}*/
		int i = 0;
		int moves = 5;
		while (i < moves) {
			nextMove = rightWallFollower();
			moveFalcon(nextMove, EXPLORING_SPEED);
			i++;
			wait(0.5);
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
		cycleLEDs(0.05);
		/*
		bluetooth.printf("Left:\r\n", );
		IR_calibration(frontLeftIR, IR_SIGDELAY, IR_SIGREST);
		bluetooth.printf("Right:\r\n");
		IR_calibration(frontRightIR, IR_SIGDELAY, IR_SIGREST);
		*/
		bluetooth.printf("Front Left Dist: %1.4f\r\n", frontLeftIR.distToWall());
		bluetooth.printf("Front Right Dist: %1.4f\r\n", frontRightIR.distToWall());
		//Gyro_calibration(150, 100);

		testBuzzer();
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