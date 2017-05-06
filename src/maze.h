/**
 * Maze class header file
 */

#ifndef __MAZE_H__
#define __MAZE_H__

/**
 * @author MMTeam1
 * @version 0.1
 */

#include "dir.h"
#include <cmath>
#include <ctime>
#include <climits>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

const int MAZE_SIZE = 16;

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
    
    // Directions to Move
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

    // Return the 4 LSB by pushing the bits that represent distance off, then bringing them back to LSB
    static unsigned char decodeWalls (int y, int x){
        unsigned char cell = the_maze[y][x];
        return cell << 12 >> 12;
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

    // Update the walls using AND operator
    static void encodeWalls (int y, int x, unsigned char newWall) {
        // Save the dist in a temporary mask
        unsigned char dist = decodeDist(y,x);

        dist = dist << 4;

        // Set the new wall to the maze index with dist using OR operator
        the_maze[y][x] = dist | newWall;
    }

    // Update the distance using the AND operator
    static void encodeDist (int y, int x, unsigned char newDist) {
        // Save the walls in a temporary mask
        unsigned char walls = decodeWalls(y, x);

        newDist = newDist << 4;

        // Set the newDist to the maze index with walls using OR operator
        the_maze[y][x] = newDist | walls;
        
    }

    // // Return an int value representing an index in maze as 1 int
    // unsigned char encodeCellIndex(int y, int x) {
    //     y = y << 5;
    //     return (unsigned char) y | x; // 10 LSB matters: Y is in 5 MSB, X in 5 LSB. 6 MSB are DONT CARES
    // }

    // // Return an x value from encoded index
    // int decodeXIndex(unsigned char encodedIndex) {
    //     return  (int) encodedIndex & 31; // Will return the x index of encoded index via mask 0000011111
    // }

    // // Return a y value from encoded index
    // int decodeYIndex(unsigned char encodedIndex) {
    //     return (int) encodedIndex & 992; // Will return y index of encoded index via mask 1111100000
    // }

};

//// Initialize static member of maze
//unsigned char Maze::the_maze[MAZE_SIZE][MAZE_SIZE] =  {
//            { 224, 208, 192, 176, 160, 144, 128, 112, 112, 128, 144, 160, 176, 192, 208, 224 },
//            { 208, 192, 176, 160, 144, 128, 112,  96,  96, 112, 128, 144, 160, 176, 192, 208 },
//            { 192, 176, 160, 144, 128, 112,  96,  80,  80,  96, 112, 128, 144, 160, 176, 192 },
//            { 176, 160, 144, 128, 112,  96,  80,  64,  64,  80,  96, 112, 128, 144, 160, 176 },
//            { 160, 144, 128, 112,  96,  80,  64,  48,  48,  64,  80,  96, 112, 128, 144, 160 },
//            { 144, 128, 112,  96,  80,  64,  48,  32,  32,  48,  64,  80,  96, 112, 128, 144 },
//            { 128, 112,  96,  80,  64,  48,  32,  16,  16,  32,  48,  64,  80,  96, 112, 128 },
//            { 112,  96,  80,  64,  48,  32,  16,   0,   0,  16,  32,  48,  64,  80,  96, 112 },
//            { 112,  96,  80,  64,  48,  32,  16,   0,   0,  16,  32,  48,  64,  80,  96, 112 },
//            { 128, 112,  96,  80,  64,  48,  32,  16,  16,  32,  48,  64,  80,  96, 112, 128 },
//            { 144, 128, 112,  96,  80,  64,  48,  32,  32,  48,  64,  80,  96, 112, 128, 144 },
//            { 160, 144, 128, 112,  96,  80,  64,  48,  48,  64,  80,  96, 112, 128, 144, 160 },
//            { 176, 160, 144, 128, 112,  96,  80,  64,  64,  80,  96, 112, 128, 144, 160, 176 },
//            { 192, 176, 160, 144, 128, 112,  96,  80,  80,  96, 112, 128, 144, 160, 176, 192 },
//            { 208, 192, 176, 160, 144, 128, 112,  96,  96, 112, 128, 144, 160, 176, 192, 208 },
//            { 224, 208, 192, 176, 160, 144, 128, 112, 112, 128, 144, 160, 176, 192, 208, 224 },
//
//};

// Init//ialize static members for mousex and mousey
//int Maze::mousex = 0;
//int Maze::mousey = 0;
//Maze::Dir Maze::current_direction = Maze::NORTH;

//vector<unsigned char> get_open_neighbors(int y, int x, );

int manhattan_dist(int x1, int x2, int y1, int y2);

int min4(int a, int b, int c, int d);

void update_distances(vector<unsigned char> &stack);

// bool fully_explored();

void explore(vector<unsigned char> &stack, int y, int x);

bool is_solved();
// TODO


// void generate_random_walls();

bool is_center(unsigned char cell);

// void set_wall(int y,int x);

unsigned char next_move(int y, int x);

void print_maze();

unsigned char encodeCellIndex(int y, int x);

int decodeXIndex(unsigned char encodedIndex);

int decodeYIndex(unsigned char encodedIndex);
    


#endif
