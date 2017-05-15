/**
 * Maze class header file
 */

#ifndef __MAZE_H__
#define __MAZE_H__

/**
 * @author MMTeam1
 * @version 0.1
 */

#include <cmath>
#include <ctime>
#include <climits>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
//#include "../config/initDevices.hpp"

using namespace std;

//#define const int MAZE_SIZE = 4;

const int MAZE_SIZE = 16;

enum Dir {

    NORTH,
    EAST,
    SOUTH,
    WEST,
    NVALID

};

class Maze {
public:

    class Cell {
    public:
        int y;
        int x;
        Cell(int y, int x) : y(y), x(x) {}

        int getCellY() {
            return this->y;
        }

        int getCellX() {
            return this->x;
        }

    };

    // Encoding for the maze in column major order. Walls represent 4 LSB, where
    // 0001 = W, 0010 = S, 0100 = E, 1000 = N, where 1 represents bit that direction
    static unsigned char the_maze[MAZE_SIZE][MAZE_SIZE];
    static int mousey;
    static int mousex;
    static bool center;
    
    // // Directions to Move
    static Dir current_direction;


    // Constructor Definition (it has none LOL)
    Maze() {
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
        unsigned char walls = Maze::decodeWalls(y, x);
        walls = walls & 4;
        return walls >> 2; 
    }

    // Push all bits off. If LSB == 1: top wall exists
    static bool has_top_wall(int y, int x) {
        unsigned char walls = Maze::decodeWalls(y, x);
        walls = walls & 8;
        return walls >> 3; 
    }
    // Return the 12 MSB by pushing the bits that represent walls off
    static int decodeDist (int y, int x) {
        unsigned char cell = the_maze[y][x];
        return (int) cell >> 4;
    }
     // 0001 = W, 0010 = S, 0100 = E, 1000 = N, where 1 represents bit that direction
    // Return the 4 LSB by pushing the bits that represent distance off, then bringing them back to LSB
    static int decodeWalls (int y, int x){
        unsigned char cell = the_maze[y][x];
        return cell & 15;
    }

    // Update the walls using AND operator
    static void encodeWalls (int y, int x, unsigned char newWall) {
        // Save the dist in a temporary mask
        // unsigned char dist = decodeDist(y,x);

        // dist = dist << 4;

        // Set the new wall to the maze index with dist using OR operator
        the_maze[y][x] = the_maze[y][x] | newWall;
    }

    // Code to updateWalls
    static void updateWalls(int y, int x, unsigned char wall) {
        // bool leftWall =         leftIR.adjWall(); 
        // if (leftWall) Maze::updateWalls(Maze::getMousey(), Maze::getMousex(), 1);

        // bool rightWall =        rightIR.adjWall();
        // if (rightWall) Maze::updateWalls(Maze::getMousey(), Maze::getMousex(), 100);

        // bool frontLeftWall =    frontLeftIR.adjWall();
        // bool frontRightWall =   frontRightIR.adjWall();
        // if (frontLeftWall && frontRightWall) Maze::updateWalls(Maze::getMousey(), Maze::getMousex(), 1000);
    }

    // Update the distance using the AND operator
    static void encodeDist (int y, int x, unsigned char newDist) {
        // Save the walls in a temporary mask
        unsigned char walls = decodeWalls(y, x);

        newDist = newDist << 4;

        // Set the newDist to the maze index with walls using OR operator
        the_maze[y][x] = newDist | walls;
        
    }

    // Get Current Direction
    static Dir getCurrentDirection () {
        return current_direction;
    }

    // Set Current Direction
    static void setCurrentDirection (Dir direction) {
        current_direction = direction;
    }

    // Flag for found center
    static void setFound (bool found) {
        center = found;
    }


};

int getMinOfNeighbors(int y, int x);

int manhattan_dist(int x1, int x2, int y1, int y2);

int min4(int a, int b, int c, int d);

void update_distances();

void explore(vector<unsigned char> &stack, int y, int x);

bool is_solved();
// TODO

bool is_center(int cell);

char next_move(int y, int x);

void print_maze();

int encodeCellIndex(int y, int x);

int decodeXIndex(int encodedIndex);

int decodeYIndex(int encodedIndex);

#endif
