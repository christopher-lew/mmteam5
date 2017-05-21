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
 *
 */
#define _IR_COEFF 2

/*
 * M: Falcon runs using the Maze class
 * D: Falcon operates in general Demo mode
 * W: Falcon operates in Wall Following mode
 * I: Used for IR Sensor calibration/testing
 * T: Falcon operates in Testing mode
 */
#define _OPERATING_MODE 'W'

#endif