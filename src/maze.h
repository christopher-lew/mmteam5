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
#include "../config/initDevices.hpp"

using namespace std;

//#define const int MAZE_SIZE = 4;

const int MAZE_SIZE = 3;

enum Direction {

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
    static int the_maze_walls[MAZE_SIZE][MAZE_SIZE];
    static int the_maze_dist[MAZE_SIZE][MAZE_SIZE];
    static int maze_actual[MAZE_SIZE][MAZE_SIZE];
    // static unsigned char the_maze[MAZE_SIZE][MAZE_SIZE];
    static int mousey;
    static int mousex;
    static bool center;
    static bool backAtStart;
    
    // // Directions to Move
    static Direction current_direction;


    // Constructor Definition (it has none LOL)
    Maze() {
    }

    // static void mazeDistInit() {

    //     int goal1 = MAZE_SIZE / 2;
    //     int goal2 = (MAZE_SIZE - 1) / 2;
    //     for (int i = 0; i < MAZE_SIZE; i++) {
    //         for (int j = 0; j < MAZE_SIZE; j++) {
    //             // Distance of the cell will be the minimum distance to the closest
    //             // one out of four middle destination cells.
    //             the_maze_dist[i][j] = min4(manhattan_dist(i, goal1, j, goal1),
    //                                              manhattan_dist(i, goal1, j, goal2),
    //                                              manhattan_dist(i, goal2, j, goal1),
    //                                              manhattan_dist(i, goal2, j, goal2));
    //             /**          cout <<"store: " << min4(manhattan_dist(i, goal1, j, goal1),
    //                                                        manhattan_dist(i, goal1, j, goal2),
    //                                                        manhattan_dist(i, goal2, j, goal1),
    //                                                        manhattan_dist(i, goal2, j, goal2)) <<
    //                                                        " in ( " << i <<" , "<< j << " )......."<<endl;
    //                       cout<< " ( " << i << " , " << j << " ):  " << maze[i][j]->dist << endl;
    //           **/
    //         }
    //     }
    // }

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
        int walls = decodeWalls(y, x);
        return walls & 16 >> 4;
    }

    // Set visited bit of the maze walls
    static void setVisited(int y, int x) {
        encodeWalls(y, x, 16); // Sets the 5th LSB to one, marking it as visited
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
        // cout << "has_right_wall == " << walls << endl;
        walls = walls & 4;
        return walls >> 2; 
    }

    // Push all bits off. If LSB == 1: top wall exists
    static bool has_top_wall(int y, int x) {
        int walls = Maze::decodeWalls(y, x);
        walls = walls & 8;
        // cout << "has_top_wall == " << walls << endl;
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

        // Push all bits off. If LSB == 1: right wall exists
    static bool actual_has_right_wall(int y, int x) {
        int walls = Maze::decodeWallsActual(y, x);
        cout << "has_right_wall == " << walls << endl;
        walls = walls & 4;
        return walls >> 2; 
    }

    // Push all bits off. If LSB == 1: top wall exists
    static bool actual_has_top_wall(int y, int x) {
        int walls = Maze::decodeWallsActual(y, x);
        walls = walls & 8;
        cout << "has_top_wall == " << walls << endl;
        return walls >> 3; 
    }

    // Mask everything except first bit. If LSB == 1: left wall exists
    static bool actual_has_left_wall(int y, int x) {
        int walls = Maze::decodeWallsActual(y, x);
        walls = walls & 1;
        cout << "has_left_wall == " << walls << endl;
        return walls;
    }

    // Mask bits for south wall. if LSB ==1 : south wall exists
    static bool actual_has_bottom_wall(int y, int x) {
        int walls = Maze::decodeWallsActual(y, x);
        cout << "has_bottom_wall == " << walls << endl;
        walls = walls & 2;
        return walls >> 1;
    }

    // Return the 12 MSB by pushing the bits that represent walls off
    static int decodeDist (int y, int x) {
        return the_maze_dist[y][x];
    }

    // 0001 = W, 0010 = S, 0100 = E, 1000 = N, where 1 represents bit that direction
    // Return the 4 LSB by pushing the bits that represent distance off, then bringing them back to LSB
    static int decodeWallsActual (int y, int x){
        int cell = maze_actual[y][x];
        cout << "decoded Walls = " << cell << endl;
        return cell & 15;
    }

    // Function to return the wall values 1111 & walls 
    static int decodeWalls (int y, int x){
    int cell = the_maze_walls[y][x];
    return cell & 15;
    }

    // Update the walls using AND operator
    static void encodeWalls (int y, int x, int newWall) {
        // Save the dist in a temporary mask
        // int dist = decodeDist(y,x);

        // dist = dist << 4;

        // Set the new wall to the maze index with dist using OR operator
        the_maze_walls[y][x] = the_maze_walls[y][x] | newWall;
    }

    // Code to updateWalls
    static void updateWalls(int y, int x) {
        bool leftWall =         leftIR.adjWall(); 
        if (leftWall) {
            Maze::encodeWalls(y, x, 1);
            if (x > 0) Maze::encodeWalls(y, x - 1, 4);
        }

        bool rightWall =        rightIR.adjWall();
        if (rightWall) {
            Maze::encodeWalls(y, x, 4);
            if (x < MAZE_SIZE - 1) Maze::encodeWalls(y, x + 1, 1);
        }

        bool frontLeftWall =    frontLeftIR.adjWall();
        bool frontRightWall =   frontRightIR.adjWall();
        if (frontLeftWall && frontRightWall) {
            Maze::encodeWalls(y, x, 8);
            if (y < MAZE_SIZE - 1) Maze::encodeWalls(y + 1, x, 2);
        }


        // if (Maze::actual_has_bottom_wall(y, x)) {
        //     Maze::encodeWalls(y, x, 2);
        //     if (y > 0) Maze::encodeWalls(y - 1, x, 8);
        // }
        // if (Maze::actual_has_top_wall(y, x)) {
            // Maze::encodeWalls(y, x, 8);
            // if (y < MAZE_SIZE - 1) Maze::encodeWalls(y + 1, x, 2);
        // }
        // if (Maze::actual_has_left_wall(y, x)) {
        //     Maze::encodeWalls(y, x, 1);
        //     if (x > 0) Maze::encodeWalls(y, x - 1, 4);
        // }
        // if (Maze::actual_has_right_wall(y, x)) {
        //     Maze::encodeWalls(y, x, 4);
        //     if (x < MAZE_SIZE - 1) Maze::encodeWalls(y, x + 1, 1);
        // }

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

    static void speedRunPrep() {
        for (int x = 0; x < MAZE_SIZE; x++) {
            for (int y = 0; y < MAZE_SIZE; y++) {
                printf("%d\n", getVisited(y, x));
                if (!getVisited(y, x)) {
                    encodeWalls(y, x, 15);
                }
            }
        }
    }

};

int getMinOfNeighbors(int y, int x);

int manhattan_dist(int x1, int x2, int y1, int y2);

int min4(int a, int b, int c, int d);

void update_distances();

void explore(vector<int> &stack, int y, int x);

bool is_solved();
// TODO

bool is_center(int cell);

bool is_start(int cell);

char next_move(int y, int x);

void print_maze();

int encodeCellIndex(int y, int x);

int decodeXIndex(int encodedIndex);

int decodeYIndex(int encodedIndex);

#endif
