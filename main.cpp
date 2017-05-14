#include "config/initModes.hpp"


#if _OPERATING_MODE == 'M'

	#include "src/maze.h"
	#include <stdio.h>
	#include <iostream>
	#include <vector>

	using namespace std;

	int main() {
        unsigned char encodedIndex = encodeCellIndex(10, 10);
        int x = decodeXIndex(encodedIndex);
        int y = decodeYIndex(encodedIndex);
        printf("%d", x);
        printf("%d", y);
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


	#define EXPLORING_SPEED 0.3
	#define _EXPLORING 1
	#define _RUNNING 2
	#define _RETURNING 3

	volatile int MOUSE_STATE = _EXPLORING;


	int main()
	{
		cycleLEDs(0.2);
		char nextMove;

		while (MOUSE_STATE == _EXPLORING)
		{
			nextMove = rightWallFollower();
			moveFalcon(nextMove, EXPLORING_SPEED);
		}
	}

// END





#elif _OPERATING_MODE == 'T'

	#include "mbed.h"
	#include "config/initDevices.hpp"
	#include "drivers/testFunctions.hpp"
	#include "drivers/debug_io.hpp"
	#include "drivers/drive_control.hpp"

	int main()
	{		
		cycleLEDs(0.05);

		while(1) {
			wait(0.1);
			print_gyro();
			testBuzzer();
		}

	}


#endif