/**
 * This header is imported in all files that depend on different falcon configuartions,
 * number of batteries, operating mode, etc.
 */

#ifndef INIT_MODES_H
#define INIT_MODES_H

/*
 * 20: Falcon v2.0 configuration
 * 21: Falcon v2.1 configuration
 * 22: Falcon v2.2 configuation 
 */
#define _FALCON_CONFIG 21

/*
 * 2: Two-Cell Battery (8.4V)
 * 3: Three-Cell Battery (12.6V)
 */ 
#define _BATTERIES 2

/*
 * Selects the IR Coefficients & Timings to be used
 */
#define _IR_COEFF 2

/*
 * D: Falcon operates in general Demo mode
 * G: Used for Gyro calibration/testing
 * I: Used for IR Sensor calibration/testing
 * M: Falcon runs using the Maze class
 * P: Used for PID tuning
 * T: Falcon operates in Testing mode
 * W: Falcon operates in Wall Following mode
 */
#define _OPERATING_MODE 'P'

#endif