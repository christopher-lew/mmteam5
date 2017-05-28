/** Maze.h
 *  Authors::Micromouse Team 1 - Javier Uruquiz, Eddie Calva, Nahoon Hwang, Christopher Lew
 *  Version 1.2
 *
 *  Functions include:
 *      Initmaze, min4, manhattenDist, isStart, isCenter, nextMove,
 *      getMinofNeighbors, updateDistances, print_maze, speedRunPrep,
 *      floodfill, encodeCellIndex, decodeXIndex, decodeYIndex
 *
 *
 */

// ------------------------------------------------------------------------- //

#ifndef __MAZE_H__
#define __MAZE_H__

#include <cmath>
#include <ctime>
#include <climits>
#include <cstdlib>
#include <string>
#include <vector>
#include <queue>
#include <iostream>

/**
 *
 * Macro For Different Working Methods:
 * OFFLINE == 1: Testing MicroMouse
 * OFFLINE == 0: Testing Computer
 *
 * MAZESIZE == x: The size of the maze
 *
 * NOTE: If OFFLINE == 0; MAZESIZE = {3, 5, 16}
 * Make more mazes of variable sizes to test on more sizes if testing on computer
 *
 */

#ifndef OFFLINE
#define OFFLINE 0
#endif

#ifndef MAZESIZE
#define MAZESIZE 16
#endif

#if OFFLINE == 1
#include "../config/initDevices.hpp"
#endif

// ------------------------------------------------------------------------- //

/**
 *  Enumeration :: Direction - direction for turning and next move decisions. Includes 4 cardinal direction
 *  and 1 invalid "default" direction
 *
 */
enum Direction {

    NORTH,
    EAST,
    SOUTH,
    WEST,
    NVALID

};

// ------------------------------------------------------------------------- //


using namespace std;

/**
 * Maze Class:
 *
 * Defines the structure of the maze and the mouse within the maze.
 * Static functions to manipulate the maze and mouse data.
 *
 * Functions include:
 *      setCenter, getCenter, setBackAtStart, getVisited, setVisited,
 *      setFlooded, getMousex, getMousey, setMousex, setMousey,
 *      hasRightWall, hasTopWall, hasLeftWall, hasBottomWall,
 *      decodeDist, decodeWalls, encodeWalls, encodeDist,
 *      getCurrentDirection, setCurrentDirection, setFound,
 *      setStartAsGoal, initMaze
 *
 *      IF OFFLINE == 0:
 *             actualHasRightWall, actualHasLeftWall, actualHasTopWall,
 *             actualHasBottomWall, decodeWallsActual
 *
 */

const int MAZE_SIZE = MAZESIZE;

class Maze {
public:

    // Encoding for the maze in column major order. Walls represent 4 LSB, where
    // 0001 = W, 0010 = S, 0100 = E, 1000 = N, where 1 represents bit that direction
    static int the_maze_walls[MAZE_SIZE][MAZE_SIZE];
    static int the_maze_dist[MAZE_SIZE][MAZE_SIZE];
    static int the_maze_visited[MAZE_SIZE][MAZE_SIZE];

// If testing on computer
#if OFFLINE == 0
    static int maze_actual[MAZE_SIZE][MAZE_SIZE];
#endif

    static int mousey;
    static int mousex;
    static bool center;
    static bool backAtStart;
    
    // Directions to Move
    static Direction current_direction;


    // Constructor Definition (it has none LOL)
    Maze() {
    }

    static void setCenter() {
        center = true;
    }

    static bool getCenter() {
        return center;
    }

    static void setBackAtStart() {
        backAtStart = true;
    }

    // Return visited bit of the maze position
    static int getVisited(int y, int x) {
        return the_maze_visited[y][x];
    }

    // Set visited bit of the maze walls
    static void setVisited(int y, int x) {
        //cout << "Setting " << x << "," << y << " as visited" << endl;
        the_maze_visited[y][x] = 1; // Sets the 5th LSB to one, marking it as visited
        //cout << getVisited(y, x) << endl;
    }

    static void setFlooded(int y, int x) {
    // Set visited bit to 0, but now means it has been previously flooded
        the_maze_visited[y][x] = 0;
    }

    // Return the x coordinate of the mouse position
    static int getMousex() {
        return mousex;
    }

    // Return the y coordinate of the mouse position
    static int getMousey() {
        return mousey;
    }

    // Set the x coordinate of the mouse position
    static void setMousex(int x) {
        mousex = x;
    }

    // Set the y coordinate of the mouse position
    static void setMousey(int y) {
        mousey = y;
    }

    // Push all bits off. If LSB == 1: right wall exists
    static bool has_right_wall(int y, int x) {
        int walls = Maze::decodeWalls(y, x);
        walls = walls & 4;
        return walls >> 2; 
    }

    // Push all bits off. If LSB == 1: top wall exists
    static bool has_top_wall(int y, int x) {
        int walls = Maze::decodeWalls(y, x);
        walls = walls & 8;
        return walls >> 3;
    }

    // Mask everything except first bit. If LSB == 1: left wall exists
    static bool has_left_wall(int y, int x) {
        int walls = Maze::decodeWalls(y, x);
        walls = walls & 1;
        // cout << "has_left_wall == " << walls << endl;
        return walls;
    }

    // Mask bits for south wall. if LSB ==1 : south wall exists
    static bool has_bottom_wall(int y, int x) {
        int walls = Maze::decodeWalls(y, x);
        // cout << "has_bottom_wall == " << walls << endl;
        walls = walls & 2;
        return walls >> 1;
    }

// If working on computer
#if OFFLINE == 0

    // Push all bits off. If LSB == 1: right wall exists
    static bool actual_has_right_wall(int y, int x) {
        int walls = Maze::decodeWallsActual(y, x);
        walls = walls & 4;
        return walls >> 2; 
    }

    // Push all bits off. If LSB == 1: top wall exists
    static bool actual_has_top_wall(int y, int x) {
        int walls = Maze::decodeWallsActual(y, x);
        walls = walls & 8;
        return walls >> 3;
    }

    // Mask everything except first bit. If LSB == 1: left wall exists
    static bool actual_has_left_wall(int y, int x) {
        int walls = Maze::decodeWallsActual(y, x);
        walls = walls & 1;
        return walls;
    }

    // Mask bits for south wall. if LSB ==1 : south wall exists
    static bool actual_has_bottom_wall(int y, int x) {
        int walls = Maze::decodeWallsActual(y, x);
        walls = walls & 2;
        return walls >> 1;
    }

    // 0001 = W, 0010 = S, 0100 = E, 1000 = N, where 1 represents bit that direction
    // Return the 4 LSB by pushing the bits that represent distance off, then bringing them back to LSB
    static int decodeWallsActual (int y, int x){
        int cell = maze_actual[y][x];
        //cout << "decoded Walls = " << cell << endl;
        return cell & 15;
    }

#endif

    // Return the 12 MSB by pushing the bits that represent walls off
    static int decodeDist (int y, int x) {
        return the_maze_dist[y][x];
    }

    // Function to return the wall values 1111 & walls 
    static int decodeWalls (int y, int x){
    int cell = the_maze_walls[y][x];
    return cell & 15;
    }

    // Update the walls using AND operator
    static void encodeWalls (int y, int x, int newWall) {
        the_maze_walls[y][x] = the_maze_walls[y][x] | newWall;
    }

    // Code to updateWalls
    static void updateWalls(int y, int x) {

#if OFFLINE == 1

        ledRed = 0;
        ledYellow = 0;
        ledGreen = 0;

        bool topWall = false;
        bool bottomWall = false; 
        bool leftWall = false; 
        bool rightWall = false;

        Direction orientation = Maze::getCurrentDirection();


        if (orientation == NORTH) {
            leftWall = leftIR.adjWall();
            rightWall = rightIR.adjWall();
            if (frontLeftIR.adjWall() && frontRightIR.adjWall()) {
                topWall = true;
            }
        }

        else if (orientation == EAST) {
            bottomWall = rightIR.adjWall();
            topWall = leftIR.adjWall();
            if (frontLeftIR.adjWall() && frontRightIR.adjWall()) {
                rightWall = true;
            }
        }

        else if (orientation == WEST) {
            bottomWall = leftIR.adjWall();
            topWall = rightIR.adjWall();
            if (frontRightIR.adjWall() && frontLeftIR.adjWall()) {
                leftWall = true;
            }
        }

        else { //if (orientation == SOUTH) {
            rightWall = leftIR.adjWall();
            leftWall = rightIR.adjWall();
            if (frontLeftIR.adjWall() && frontRightIR.adjWall()) {
                bottomWall = true;
            }
        }
        
    if ( rightWall)  {
        ledGreen = 1;
    }

    if ( leftWall)  {
        ledYellow = 1;
    }

    if ( topWall)  {
        ledRed = 1;
    }

    if (bottomWall) {
        
    }

    if (leftWall) {
        Maze::encodeWalls(y, x, 1);
        if (x > 0) Maze::encodeWalls(y, x - 1, 4);
    }

    if (rightWall) {
        Maze::encodeWalls(y, x, 4);
        if (x < MAZE_SIZE - 1) Maze::encodeWalls(y, x + 1, 1);
    }

    if (topWall) {
        Maze::encodeWalls(y, x, 8);
        if (y < MAZE_SIZE - 1) Maze::encodeWalls(y + 1, x, 2);
    }

    if (bottomWall) {
        Maze::encodeWalls(y, x, 2);
        if (y > 0) Maze::encodeWalls(y - 1, x, 8);
    }
#else // Working on online maze

        if (Maze::actual_has_bottom_wall(y, x)) {
            Maze::encodeWalls(y, x, 2);
            if (y > 0) Maze::encodeWalls(y - 1, x, 8);
        }
        if (Maze::actual_has_top_wall(y, x)) {
            Maze::encodeWalls(y, x, 8);
            if (y < MAZE_SIZE - 1) Maze::encodeWalls(y + 1, x, 2);
        }
        if (Maze::actual_has_left_wall(y, x)) {
            Maze::encodeWalls(y, x, 1);
            if (x > 0) Maze::encodeWalls(y, x - 1, 4);
        }
        if (Maze::actual_has_right_wall(y, x)) {
            Maze::encodeWalls(y, x, 4);
            if (x < MAZE_SIZE - 1) Maze::encodeWalls(y, x + 1, 1);
        }
#endif

    }

    // Update the distance using the AND operator
    static void encodeDist (int y, int x, int newDist) {
        // Save the walls in a temporary mask
        // int walls = decodeWalls(y, x);

        // newDist = newDist << 4;

        // Set the newDist to the maze index with walls using OR operator
        the_maze_dist[y][x] = newDist;
        
    }

    // Get Current Direction
    static Direction getCurrentDirection () {
        return current_direction;
    }

    // Set Current Direction
    static void setCurrentDirection (Direction direction) {
        current_direction = direction;
    }

    // Flag for found center
    static void setFound (bool found) {
        center = found;
    }

    static void setStartAsGoal () {

        for (int x = 0; x < MAZE_SIZE; x++) {
            for (int y = 0; y < MAZE_SIZE; y++ ) {
                the_maze_dist[y][x] = y + x;
            }
        }
    }

    static void initMaze();

    static void resetMazeDist();

};

// ------------------------------------------------------------------------- //


void speedRunPrep();

void floodfill();

int getMinOfNeighbors(int y, int x);

int manhattan_dist(int x1, int x2, int y1, int y2);

int min4(int a, int b, int c, int d);

void update_distances(int y, int x);

bool is_center(int cell);

bool is_start(int cell);

char next_move(int y, int x);

void print_maze();

int encodeCellIndex(int y, int x);

int decodeXIndex(int encodedIndex);

int decodeYIndex(int encodedIndex);

#endif

// ------------------------------------------------------------------------- //

// EOF
