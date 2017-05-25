/**
 * PID Controller for the Falcon.
 */

#ifndef PID_H
#define PID_H

#include "mbed.h"
#include "../config/initModes.hpp"
#include "../config/initConstants.hpp"
#include "../config/initDevices.hpp"
#include "testFunctions.hpp"

#define PID_LtoR_OFFSET -0.1 // cm
#define PID_SIDE_ALIGN 6.0 // cm
#define PID_FRONT_ALIGN 4.5

#define PID_SAMPLE_PERIOD 0.005 // seconds

#define PID_DECCEL_SPEED 0.06


class PID_Controller
{
public:
	PID_Controller(void);

	bool keepStraight();
	void alignUsingSides(bool leftWall, bool rightWall);
	void alignToFrontWall();
	void HailMary();
	void turn(char direction);
	void calibration(float _KP, float _KD, int samples, float sample_period, bool print_pidLog);

	int getEncoderDistance();
	void resetEncoders();

private:
	volatile float errorP;
	volatile float oldErrorP;
	volatile float errorD;
	volatile float totalError;
};

#endif