#include "maze.h"

#include <stdio.h>
#include <stdlib.h>

// 

Direction Maze::current_direction = NORTH;

// Japan 1991 
// unsigned char Maze::the_maze[MAZE_SIZE][MAZE_SIZE] = {
//     { 228, 209, 200, 184, 168, 152, 136, 120, 120, 136, 152, 168, 184, 200, 216, 224 },
//     { 208, 196, 187, 170, 146, 138, 114,  106,  106, 122, 138, 154, 170, 186, 194, 209 },
//     { 196, 177, 170, 146, 132, 127,  101,  83,  90,  106, 122, 130, 154, 166, 181, 193 },
//     { 180, 169, 154, 140, 113,  106,  88,  64,  74,  90,  102, 117, 143, 149, 165, 177 },
//     { 168, 152, 130, 122,  104,  90,  70,  57,  54,  73,  90,  105, 122, 132, 149, 161 },
//     { 154, 138, 120,  98,  90,  74,  56,  38,  41,  54,  73,  90,  102, 118, 134, 145 },
//     { 138, 122, 106,  88,  66,  50,  42,  24,  30,  41,  54,  79,  86,  102, 118, 129 },
//     { 114,  106,  90,  70,  54,  38,  19,   2,   6,  23,  41,  44,  70,  86,  102, 113 },
//     { 112,  102,  95,  70,  57,  44,  22,   9,   12,  22,  39,  57,  64,  92,  102, 113 },
//     { 128, 112,  96,  80,  64,  48,  32,  16,  16,  32,  48,  64,  80,  96, 112, 128 },
//     { 144, 128, 112,  96,  80,  64,  48,  32,  32,  48,  64,  80,  96, 112, 128, 144 },
//     { 160, 144, 128, 112,  96,  80,  64,  48,  48,  64,  80,  96, 112, 128, 144, 160 },
//     { 176, 160, 144, 128, 112,  96,  80,  64,  64,  80,  96, 112, 128, 144, 160, 176 },
//     { 192, 176, 160, 144, 128, 112,  96,  80,  80,  96, 112, 128, 144, 160, 176, 192 },
//     { 208, 192, 176, 160, 144, 128, 112,  96,  96, 112, 128, 144, 160, 176, 192, 208 },
//     { 224, 208, 192, 176, 160, 144, 128, 112, 112, 128, 144, 160, 176, 192, 208, 224 },
// };

//Initialize static member of maze
// unsigned char Maze::the_maze[MAZE_SIZE][MAZE_SIZE] =  {
//     { 224, 208, 192, 176, 160, 144, 128, 112, 112, 128, 144, 160, 176, 192, 208, 224 },
//     { 208, 192, 176, 160, 144, 128, 112,  96,  96, 112, 128, 144, 160, 176, 192, 208 },
//     { 192, 176, 160, 144, 128, 112,  96,  80,  80,  96, 112, 128, 144, 160, 176, 192 },
//     { 176, 160, 144, 128, 112,  96,  80,  64,  64,  80,  96, 112, 128, 144, 160, 176 },
//     { 160, 144, 128, 112,  96,  80,  64,  48,  48,  64,  80,  96, 112, 128, 144, 160 },
//     { 144, 128, 112,  96,  80,  64,  48,  32,  32,  48,  64,  80,  96, 112, 128, 144 },
//     { 128, 112,  96,  80,  64,  48,  32,  16,  16,  32,  48,  64,  80,  96, 112, 128 },
//     { 112,  96,  80,  64,  48,  32,  16,   0,   0,  16,  32,  48,  64,  80,  96, 112 },
//     { 112,  96,  80,  64,  48,  32,  16,   0,   0,  16,  32,  48,  64,  80,  96, 112 },
//     { 128, 112,  96,  80,  64,  48,  32,  16,  16,  32,  48,  64,  80,  96, 112, 128 },
//     { 144, 128, 112,  96,  80,  64,  48,  32,  32,  48,  64,  80,  96, 112, 128, 144 },
//     { 160, 144, 128, 112,  96,  80,  64,  48,  48,  64,  80,  96, 112, 128, 144, 160 },
//     { 176, 160, 144, 128, 112,  96,  80,  64,  64,  80,  96, 112, 128, 144, 160, 176 },
//     { 192, 176, 160, 144, 128, 112,  96,  80,  80,  96, 112, 128, 144, 160, 176, 192 },
//     { 208, 192, 176, 160, 144, 128, 112,  96,  96, 112, 128, 144, 160, 176, 192, 208 },
//     { 224, 208, 192, 176, 160, 144, 128, 112, 112, 128, 144, 160, 176, 192, 208, 224 },

// };

// int Maze::maze_actual[MAZE_SIZE][MAZE_SIZE] = {
//    { 4, 1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0},
//    { 0, 4, 11, 10, 2, 10, 2, 10, 10, 10, 10, 10, 10, 10, 6, 1},
//    { 4, 1, 10, 2, 4 , 15, 5, 3, 10, 10, 10, 2, 10, 6, 5, 1 },
//    { 4, 9, 10, 12, 1 , 10, 8, 0, 10, 10, 6, 5, 15, 5, 5, 1 },
//    { 8, 10, 2, 10, 8 , 10, 6, 9, 6, 15, 5, 9, 10, 4, 5, 1 },
//    { 10, 10, 8, 2, 10 , 10, 8, 6, 9, 6, 9, 10, 6, 5, 5, 1 },
//    { 10, 10, 10, 8, 2 , 2, 10, 8, 14, 9, 6, 15, 5, 5, 5, 1 },
//    { 2, 10, 10, 6, 5 , 5, 3, 2, 6, 7, 9, 6, 5, 5, 5, 1 },
//    { 0, 6, 15, 5, 9 , 12, 5, 9, 12, 5, 7, 9, 0, 12, 5, 1 },
//    { 4, 9, 6, 9, 10 , 6, 1, 14, 3, 8, 0, 6, 5, 3, 12, 1 },
//    { 0, 6, 9, 6, 15 , 5, 5, 11, 0, 10, 4, 13, 5, 9, 10, 0 },
//    { 4, 9, 6, 9, 6 , 9, 4, 11, 0, 14, 1, 10, 8, 10, 2, 0 },
//    { 0, 6, 9, 6, 9 , 10, 8, 11, 0, 14, 9, 2, 10, 2, 12, 1 },
//    { 4, 9, 6, 9, 6 , 11, 2, 10, 0, 14, 3, 8, 2, 8, 10, 0 },
//    { 4, 15, 9, 6, 9 , 6, 5, 11, 0, 14, 3, 2, 8, 10, 2, 8 },
//    { 0, 2, 2, 0, 2 , 0, 0, 2, 0, 2, 2, 0, 2, 2, 4, 3 },
// };

// int Maze::the_maze_dist[MAZE_SIZE][MAZE_SIZE] = {

//    { 14, 13, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14},
//    { 13, 12, 11, 10,  9, 8, 7, 6, 6, 7, 8,  9, 10, 11, 12, 13},
//    { 12, 11, 10,  9,  8, 7, 6, 5, 5, 6, 7,  8,  9, 10, 11, 12},
//    { 11, 10,  9,  8,  7, 6, 5, 4, 4, 5, 6,  7,  8,  9, 10, 11},
//    { 10,  9,  8,  7,  6, 5, 4, 3, 3, 4, 5,  6,  7,  8,  9, 10},
//    {  9,  8,  7,  6,  5, 4, 3, 2, 2, 3, 4,  5,  6,  7,  8,  9},
//    {  8,  7,  6,  5,  4, 3, 2, 1, 1, 2, 3,  4,  5,  6,  7,  8},
//    {  7,  6,  5,  4,  3, 2, 1, 0, 0, 1, 2,  3,  4,  5,  6,  7},
//    {  7,  6,  5,  4,  3, 2, 1, 0, 0, 1, 2,  3,  4,  5,  6,  7},
//    {  8,  7,  6,  5,  4, 3, 2, 1, 1, 2, 3,  4,  5,  6,  7,  8},
//    {  9,  8,  7,  6,  5, 4, 3, 2, 2, 3, 4,  5,  6,  7,  8,  9},
//    { 10,  9,  8,  7,  6, 5, 4, 3, 3, 4, 5,  6,  7,  8,  9, 10},
//    { 11, 10,  9,  8,  7, 6, 5, 4, 4, 5, 6,  7,  8,  9, 10, 11},
//    { 12, 11, 10,  9,  8, 7, 6, 5, 5, 6, 7,  8,  9, 10, 11, 12},
//    { 13, 12, 11, 10,  9, 8, 7, 6, 6, 7, 8,  9, 10, 11, 12, 13},
//    { 14, 13, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14},

// };

// int Maze::the_maze_walls[MAZE_SIZE][MAZE_SIZE] = {

//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

// };

// int Maze::the_maze_visited[MAZE_SIZE][MAZE_SIZE] = {

//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//    { 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },

// };

 int Maze::maze_actual[MAZE_SIZE][MAZE_SIZE] = {
     {4, 1, 0},
     {4, 13, 1},
     {0, 2, 0},

 };

 int Maze::the_maze_dist[MAZE_SIZE][MAZE_SIZE] = {
     {2, 1, 2},
     {1, 0, 1},
     {2, 1, 2},
 };

 int Maze::the_maze_walls[MAZE_SIZE][MAZE_SIZE] = {
     {0, 0, 0},
     {0, 0, 0},
     {0, 0, 0},
 };
 
 int Maze::the_maze_visited[MAZE_SIZE][MAZE_SIZE] = {
     {0, 0, 0},
     {0, 0, 0},
     {0, 0, 0},
};

// 5x5
//int Maze::maze_actual[MAZE_SIZE][MAZE_SIZE] = {
//
//    {4, 1, 8, 8, 8},
//    {4, 1, 10, 10, 2},
//    {4, 5, 7, 3, 0},
//    {0, 4, 1, 12, 1},
//    {4, 5, 1, 2, 0},
//};
//int Maze::the_maze_dist[MAZE_SIZE][MAZE_SIZE] = {
//    
//    {4, 3, 2, 3, 4},
//    {3, 2, 1, 2, 3},
//    {2, 1, 0, 1, 2},
//    {3, 2, 1, 2, 3},
//    {4, 3, 2, 3, 4},
//
//};
//
//int Maze::the_maze_walls[MAZE_SIZE][MAZE_SIZE] = {
//
//    {0, 0, 0, 0, 0},
//    {0, 0, 0, 0, 0},
//    {0, 0, 0, 0, 0},
//    {0, 0, 0, 0, 0},
//    {0, 0, 0, 0, 0},
//
//};


bool Maze::center = false;
bool Maze::backAtStart = false;

// #if MAZE_SIZE == 16
// Initialize static member of maze
// unsigned char Maze::the_maze[MAZE_SIZE][MAZE_SIZE] =  {
//             { 224, 208, 192, 176, 160, 144, 128, 112, 112, 128, 144, 160, 176, 192, 208, 224 },
//             { 208, 192, 176, 160, 144, 128, 112,  96,  96, 112, 128, 144, 160, 176, 192, 208 },
//             { 192, 176, 160, 144, 128, 112,  96,  80,  80,  96, 112, 128, 144, 160, 176, 192 },
//             { 176, 160, 144, 128, 112,  96,  80,  64,  64,  80,  96, 112, 128, 144, 160, 176 },
//             { 160, 144, 128, 112,  96,  80,  64,  48,  48,  64,  80,  96, 112, 128, 144, 160 },
//             { 144, 128, 112,  96,  80,  64,  48,  32,  32,  48,  64,  80,  96, 112, 128, 144 },
//             { 128, 112,  96,  80,  64,  48,  32,  16,  16,  32,  48,  64,  80,  96, 112, 128 },
//             { 112,  96,  80,  64,  48,  32,  16,   0,   0,  16,  32,  48,  64,  80,  96, 112 },
//             { 112,  96,  80,  64,  48,  32,  16,   0,   0,  16,  32,  48,  64,  80,  96, 112 },
//             { 128, 112,  96,  80,  64,  48,  32,  16,  16,  32,  48,  64,  80,  96, 112, 128 },
//             { 144, 128, 112,  96,  80,  64,  48,  32,  32,  48,  64,  80,  96, 112, 128, 144 },
//             { 160, 144, 128, 112,  96,  80,  64,  48,  48,  64,  80,  96, 112, 128, 144, 160 },
//             { 176, 160, 144, 128, 112,  96,  80,  64,  64,  80,  96, 112, 128, 144, 160, 176 },
//             { 192, 176, 160, 144, 128, 112,  96,  80,  80,  96, 112, 128, 144, 160, 176, 192 },
//             { 208, 192, 176, 160, 144, 128, 112,  96,  96, 112, 128, 144, 160, 176, 192, 208 },
//             { 224, 208, 192, 176, 160, 144, 128, 112, 112, 128, 144, 160, 176, 192, 208, 224 },

// };

// Initialize static members for mousex and mousey
int Maze::mousex = 0;
int Maze::mousey = 0;

//FUNCTION to take the minimum of 4 distances
int min4(int a, int b, int c, int d) {
    int min;
    (a < b) ? min = a : min = b;
    if (c < min) min = c;
    if (d < min) min = d;
    return min;
}

// FUNCTION to calculate the manhatten distance between two points
int manhattan_dist(int x1, int x2, int y1, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// FUNCTIOn to check whether mouse is back at start
bool is_start(int cell) {
    int x = decodeXIndex(cell);
    int y = decodeYIndex(cell);
    int xgoal = 0;
    int ygoal = 0;

    if (manhattan_dist(y, ygoal, x, xgoal) == 0) { return true; }

    return false;
}

// FUNCTION to check whether the mouse is at the center cell
bool is_center(int cell) { // cell is encoded index
  int x = decodeXIndex(cell);
  int y = decodeYIndex(cell);
  int goal1 = MAZE_SIZE / 2;
  int goal2 = (MAZE_SIZE - 1) / 2;

  // Checks if the manhattan_dist of the current cell to the 4 goal states is 0
  if (manhattan_dist(y, goal1, x, goal1) == 0 ||
      manhattan_dist(y, goal1, x, goal2) == 0 ||
      manhattan_dist(y, goal2, x, goal1) == 0 ||
      manhattan_dist(y, goal2, x, goal2) == 0)
      // If so, return TRUE
      { return true; }
  // Else, not the center, return false
  return false;
}

// FUNCTION to figure out the next move by the smallest distance
char next_move(int currX, int currY) { // (Maze::Cell *current)
    bool hasNextMove = false;
    int x, y, minx, miny, i, j;
    int x_goal = MAZE_SIZE / 2;
    int y_goal = MAZE_SIZE - 1 / 2;

    Direction currDir = Maze::getCurrentDirection();
    // Initial positions of the next move
    minx = 0;
    miny = 0;
    // Initial position of mouse
    x = Maze::getMousex();
    y = Maze::getMousey();
    // checks the next cell with the smallest distance
    for(i = -1; i <= 1; i++){
        for(j = -1; j <= 1; j++){

            int next_x = x + i;
            int next_y = y + j;

            // ignore diagonal cells for now
            if (next_x != x && next_y != y)  continue;

            // pass over non open right neighbors
            else if (Maze::has_right_wall(y, x) && next_x == x + 1) continue;
            // pass over non open top neightbors
            else if (Maze::has_top_wall(y, x) && next_y == y + 1) continue;
            // pass over non open left neighbors
            else if (Maze::has_left_wall(y, x) && next_x == x - 1) continue;
            // pass over non open bottom neighbors
            else if (Maze::has_bottom_wall(y, x) && next_y == y - 1) continue;

            // means cell does not exist, these are border cells
            else if(next_y < 0 || next_y >= MAZE_SIZE || next_x < 0 || next_x >= MAZE_SIZE) continue;

            // if the next cell has a smaller distance then check
            if (Maze::decodeDist(next_y,next_x) < Maze::decodeDist(y, x)){
                // breaking ties
                if((next_x == minx) && (next_y == miny)){
                    // check if the mouse is facing straight 0->1->2->3 counter-clockwise
                   if((currDir == NORTH && next_x > y) || (currDir == SOUTH && next_y < y) ||
                      (currDir == WEST && next_x < x) || (currDir == EAST && next_x > x)){
                       minx = x + i;
                       miny = y + j;
                       hasNextMove = true;
                       cout << "hi" << endl;
                       //cout << "minx = " << minx << endl;
//                       cout << "miny = " << miny << endl;
                       continue;
                   }
                    //check for whichever is closer to the center of the maze
                   else{
                       double prev_to_goal = sqrt(pow(x_goal - minx, 2.0) + pow(y_goal - miny, 2.0));
                       double curr_to_goal = sqrt(pow(x_goal - next_x, 2.0) + pow(y_goal - next_y, 2.0));
                       if(curr_to_goal < prev_to_goal){
                            minx = x + i;
                            miny = y + j;
                            hasNextMove = true;
                           // cout << "minx = " << minx << endl;
//                            cout << "miny = " << miny << endl;
                           continue;
                       }
                   }
                }
                else {
                    // not tie condition
                    minx = x + i;
                    miny = y + j;
                    hasNextMove = true;
                }


            }
            
        }
    }


    cout << hasNextMove << endl;
    cout << "minx = " << minx << endl;
    cout << "miny = " << miny << endl;

    int newX = minx;
    int newY = miny;
    if (!hasNextMove) return 'Z';
    Maze::setVisited(Maze::getMousey(), Maze::getMousex());
    // Update the mouse position
    Maze::setMousex(newX);
    Maze::setMousey(newY);


    Direction turning = NVALID;

    // signals next cell's direction
    // We want to go left in the maze! 
    if((minx < x) && (miny == y)){

        if (currDir == NORTH) {
            Maze::setCurrentDirection(turning=WEST);
            return 'L';
        }
        if (currDir == SOUTH) {
            Maze::setCurrentDirection(turning=WEST);
            return 'R';
        }
        if (currDir == EAST) {
            Maze::setCurrentDirection(turning=WEST);
            return 'S';
        }
        if (currDir == WEST) {
            Maze::setCurrentDirection(turning=WEST);
            return 'F';
        }
    }

    // We want to go forward in the maze!
    else if((minx == x) && (miny > y)){
       if (currDir == NORTH) {
            Maze::setCurrentDirection(turning=NORTH);
            return 'F';
        }
        if (currDir == SOUTH) {
            Maze::setCurrentDirection(turning=NORTH);
            return 'S';
        }
        if (currDir == EAST) {
            Maze::setCurrentDirection(turning=NORTH);
            return 'L';
        }
        if (currDir == WEST) {
            Maze::setCurrentDirection(turning=NORTH);
            return 'R';
        }
    }

    // We want to go right in the maze!
    else if((minx > x) && (miny == y)){
       if (currDir == NORTH) {
            Maze::setCurrentDirection(turning=EAST);
            return 'R';
        }
        if (currDir == SOUTH) {
            Maze::setCurrentDirection(turning=EAST);
            return 'L';
        }
        if (currDir == EAST) {
            Maze::setCurrentDirection(turning=EAST);
            return 'F';
        }
        if (currDir == WEST) {
            Maze::setCurrentDirection(turning=EAST);
            return 'S';
        }
    }

    // We want to go south in the maze!
    else {// if((minx == x) && (miny < y)){
       if (currDir == NORTH) {
            Maze::setCurrentDirection(turning=SOUTH);
            return 'S';
        }
        if (currDir == SOUTH) {
            Maze::setCurrentDirection(turning=SOUTH);
            return 'F';
        }
        if (currDir == EAST) {
            Maze::setCurrentDirection(turning=SOUTH);
            return 'R';
        }
        if (currDir == WEST) {
            Maze::setCurrentDirection(turning=SOUTH);
            return 'L';
        }
    }

    return 'Z'; // Should never reach, but choooses to go forward lawls.
}

// FUNCTION to get open neighbors of given cell index, and return minimum value
int getMinOfNeighbors(int y, int x) {

    int min = 256;

    // Add all neighbors to neighbor stack, if open (ie no wall), find the min of open neighbors
    // check top neighbor
    if (y < MAZE_SIZE - 1) {
        int topNeighbor = Maze::decodeDist(y + 1, x);
        if (!Maze::has_top_wall(y, x) && topNeighbor < min) {
            min = topNeighbor;
        }
    }
    // check right neighbor
    if (x < MAZE_SIZE - 1) {
        int rightNeighbor = Maze::decodeDist(y, x + 1);   
        if (!Maze::has_right_wall(y, x) && rightNeighbor < min) {
            min = rightNeighbor;
        }
    }
    // check bottom neighbor
    if (y > 0) {
        int bottomNeighbor = Maze::decodeDist(y - 1, x);
        if (!Maze::has_bottom_wall(y, x) && bottomNeighbor < min) {
            min = bottomNeighbor;
        }

    }
    // check left neighbor
    if (x > 0) {
        int leftNeightbor = Maze::decodeDist(y, x - 1);
        if (!Maze::has_left_wall(y, x) && leftNeightbor < min) {
            min = leftNeightbor;
        }
    }

    return min;
    // if return value is 2000, cell is unreachable and has no open neighbors

}
// FUNCTION to update the distances.
void update_distances(int y, int x) {

    /** Function Info
     * Function pushes current position onto the stack.
     * While stack is not empty, pop the top, then find the minimum value of open neighbors
     * 
     * Get the minimum distance value, this represents the direction we would want to move to because it is open,
     * so it should represent the next best move to the center at that point in the algorithm.
     * 
     * If currVal is not exactly 1 more than min value, make curr value 1 greater than min.
     */

    // // Initial x, y values
    // int x, y;  

    // x = Maze::getMousex();
    // y = Maze::getMousey();

    int current = encodeCellIndex(y, x);   

    // if (is_center(current)) {
    //     printf("FOUND CENTER\n");
    // }

    // Stack to update the distances, and push current cell onto stack
    std::vector <int> stack;
    stack.push_back(current);

    while (!stack.empty()) {

        current = stack.back();
        stack.pop_back();
        //printf("current is: %d\r\n", current);

        //printf("current x, y = %d, %d\r\n", x, y );
        x = decodeXIndex(current);
        y = decodeYIndex(current);

        int currentDist = Maze::decodeDist(y, x);
        
        // Find the minimum distance value of all the open neighbors of current cell
        int min = getMinOfNeighbors(y, x);
        printf("min = %d\r\n", min);
        printf("currentDist = %d\r\n", currentDist);

        // This means that the current cell is unreachable, so continue WHO CARES ABOUT IT LOLOLOL
        if (min == 256) {
            //cout << "JSDA:LKDJ:LKWJE BAD" << endl;
            continue;
        }

        // Is current cell 1 + min of adjacent cells
        if (currentDist == 1 + min) { continue; }

        else {

            printf("Making maze[%d][%d] = %d\r\n", y, x, min + 1);
            Maze::encodeDist(y, x, min + 1); // Since it is less than min, make it 1 greater than min

            // Pushback all the neighbors again to the stack if they exist
            if (y  < MAZE_SIZE - 1 && !Maze::has_top_wall(y, x)) stack.push_back(encodeCellIndex(y + 1, x)); // Top neighbor
            if (y  > 0 && !Maze::has_bottom_wall(y, x)) stack.push_back(encodeCellIndex(y - 1, x)); // Bottom Neighbor
            if (x  < MAZE_SIZE - 1 && !Maze::has_right_wall(y, x)) stack.push_back(encodeCellIndex(y, x + 1)); // Right Neighbor
            if (x  > 0 && !Maze::has_left_wall(y, x)) stack.push_back(encodeCellIndex(y, x - 1)); // Left Neighbor
        }
    }

}

// FUNCTION to print maze
void print_maze() {
    
    // print top wall
    for (int i = 0; i < MAZE_SIZE; i++) {
        printf("+---");
    }
    printf("+\r\n");
    
    int rows = MAZE_SIZE + (MAZE_SIZE - 1);
    int y;
    
    for (int i = 0; i < rows; i++) {
        if (i % 2 == 0) {
            y = MAZE_SIZE - 1 - i / 2;
        }
        else {
            y = MAZE_SIZE - 1 - (i / 2 + 1);
        }

        for (int j = 0; j < MAZE_SIZE; j++) {
            
            if (i % 2 != 0) {
                if (Maze::has_top_wall(y, j)) {
                    printf("+---");
                }
                else {
                    printf("+   ");
                }
                if (j == MAZE_SIZE - 1) {
                    printf("+");
                }
            }
            
            else {
                if (j == 0) {
                    printf("|");
                }
                
                int dist = (int) Maze::decodeDist(y, j);
                if (y == Maze::getMousey() && j == Maze::getMousex()) {
                    printf(" M ");

                }
                // else if (Maze::getVisited(y, j)) {
                //     printf(" * ");
                // }
                else if (dist > 99) {
                    printf("%d", dist);
                }
                else if (dist > 9) {
                    printf(" %d", dist);
                }
                else {
                    printf(" %d ", dist);
                }
                
                if ((Maze::has_right_wall(y, j) || j == MAZE_SIZE - 1)) {
                    printf("|"); 
                }
                else {
                    printf(" ");
                }
            }
        }
        printf("\r\n");
    }
    
    // print bottom wall
    for (int i = 0; i < MAZE_SIZE; i++) {
        printf("+---");
    }
    printf("+\r\n");

    //cout << "End Print Function" << endl;
    printf("\r\n");

}

void speedRunPrep() {
    // Maze::encodeDist(0, 0, 2);

    for (int x = 0; x < MAZE_SIZE; x++) {
        for (int y = 0; y < MAZE_SIZE; y++) {

            //printf("%d\n", getVisited(y, x));
            if (!Maze::getVisited(y, x) && !is_center(encodeCellIndex(y,x))) {
                if (y < MAZE_SIZE - 1 && !Maze::has_top_wall(y, x)) Maze::encodeWalls(y + 1, x, 2); // Top neighbor
                if (y > 0 && !Maze::has_bottom_wall(y, x)) Maze::encodeWalls(y - 1, x, 8); // Bottom Neighbor
                if (x < MAZE_SIZE - 1 && !Maze::has_right_wall(y, x)) Maze::encodeWalls(y, x + 1, 1); // Right Neighbor
                if (x > 0 && !Maze::has_left_wall(y, x)) Maze::encodeWalls(y, x - 1, 4); // Left Neighbor
                Maze::encodeWalls(y, x, 15);
                Maze::encodeDist(y, x, 256);
            }

        }
    }

    //print_maze();
    //getchar();

    for (int x = 0; x < MAZE_SIZE; x++) {
        for (int y = 0; y < MAZE_SIZE; y++) {
            int wallCount = 0;
            if (Maze::has_bottom_wall(y, x)) wallCount++;
            if (Maze::has_left_wall(y, x)) wallCount++;
            if (Maze::has_top_wall(y, x)) wallCount++;
            if (Maze::has_right_wall(y, x)) wallCount++;

            if (wallCount >= 3 && !is_center(encodeCellIndex(y,x))) {
                // If has three or more walls, encode 15
                cout << x << " ," << y << " has wall count > 3" << endl;
                // Find open and encode that wall 
                if (!Maze::has_top_wall(y, x)) Maze::encodeWalls(y + 1, x, 2); // Top neighbor
                if (!Maze::has_bottom_wall(y, x)) Maze::encodeWalls(y - 1, x, 8); // Bottom Neighbor
                if (!Maze::has_right_wall(y, x)) Maze::encodeWalls(y, x + 1, 1); // Right Neighbor
                if (!Maze::has_left_wall(y, x)) Maze::encodeWalls(y, x - 1, 4); // Left Neighbor
                
                Maze::encodeWalls(y, x, 15);

                Maze::encodeDist(y, x, 256);
            }
        }
    }

    // int goal1 = MAZE_SIZE / 2;
    // int goal2 = (MAZE_SIZE - 1) / 2;

    // Maze::encodeDist(goal1, goal1, 0);
    // Maze::encodeDist(goal1, goal2, 0);
    // Maze::encodeDist(goal2, goal1, 0);
    // Maze::encodeDist(goal2, goal2, 0);

    for (int x = 0; x < MAZE_SIZE; x++) {
        for (int y = 0; y < MAZE_SIZE; y++) {
            if (Maze::decodeDist(y, x) != 256) {
                update_distances(y, x);
    //             int min = min4(manhattan_dist(y, goal1, x, goal1),
    //                 manhattan_dist(y, goal1, x, goal2),
    //                 manhattan_dist(y, goal2, x, goal1),
    //                 manhattan_dist(y, goal2, x, goal2));
    //             Maze::encodeDist(y, x, min);

            }
        }
    }
    // print_maze();
    // getchar();
}

void floodfill() {
    int goal1 = MAZE_SIZE / 2;
    int goal2 = (MAZE_SIZE - 1) / 2;

    Maze::encodeDist(goal1, goal1, 0);
    Maze::encodeDist(goal1, goal2, 0);
    Maze::encodeDist(goal2, goal1, 0);
    Maze::encodeDist(goal2, goal2, 0);

    // checks the next cell with the smallest distance

    std::queue<int> queue;
    queue.push(encodeCellIndex(goal1, goal1));
    queue.push(encodeCellIndex(goal1, goal2));
    queue.push(encodeCellIndex(goal2, goal1));
    queue.push(encodeCellIndex(goal2, goal2));

    while (!queue.empty()) {

        int current = queue.front();
        queue.pop();
        int x = decodeXIndex(current);
        int y = decodeYIndex(current);
        if (!Maze::getVisited(y, x)) continue; // Means flooded
        int min = getMinOfNeighbors(y, x);
        Maze::setFlooded(y, x);
        Maze::encodeDist(y, x, min + 1);

        // Pushback all the neighbors again to the stack if they exist
        if (y  < MAZE_SIZE - 1 && !Maze::has_top_wall(y, x)) queue.push(encodeCellIndex(y + 1, x)); // Top neighbor
        if (y  > 0 && !Maze::has_bottom_wall(y, x)) queue.push(encodeCellIndex(y - 1, x)); // Bottom Neighbor
        if (x  < MAZE_SIZE - 1 && !Maze::has_right_wall(y, x)) queue.push(encodeCellIndex(y, x + 1)); // Right Neighbor
        if (x  > 0 && !Maze::has_left_wall(y, x)) queue.push(encodeCellIndex(y, x - 1)); // Left Neighbor
    }

}   

// Return an int value representing an index in maze as 1 int
int encodeCellIndex(int y, int x) {
    //printf("%d, %d, is being encoded : ", x, y);
    y = y << 5;
    int encodedVal = y | x;
    // cout << "encoded value = " << encodedVal << endl;
    return encodedVal; // 10 LSB matters: Y is in 5 MSB, X in 5 LSB. 6 MSB are DONT CARES
}

// Return an x value from encoded index
int decodeXIndex(int encodedIndex) {
    int toReturn = encodedIndex & 31;
    // cout << "decoded x value = " << toReturn << endl;
    return  toReturn; // Will return the x index of encoded index via mask 0000011111
}

// Return a y value from encoded index
int decodeYIndex(int encodedIndex) {
    int toReturn = encodedIndex & 992;
    if (encodedIndex > 31) toReturn = toReturn >> 5;
    // cout << "decoded y value = " << toReturn << endl;
    return toReturn; // Will return y index of encoded index via mask 1111100000
}
int main() {

   int state = 1 ;
   Maze();
   // cycleLEDs(0.1);
   // wait(5);
   // cycleLEDs(0.1);

   // while (state = 0) { // Runnable State

   //     if (frontLeftIR.adjWall() && frontRightWall.adjWall()){
   //         cycleLEDs(0.1);
   //         cycleMFs(0.02);
   //         testBuzzer();

   //         state++;
   //         wait(5);
   //     }       
   // }

//    while (state == 1) {
       
//        if (is_center(encodeCellIndex(Maze::getMousey(), Maze::getMousex()))) {
//            // testBuzzer();
//            Maze::setStartAsGoal();
//            state++;
//            continue;
//        }
//        getchar();
//        //cycleMFs(0.02);
//        Maze::updateWalls(Maze::getMousey(), Maze::getMousex());
//        update_distances(Maze::getMousey(), Maze::getMousex());
//        next_move(Maze::getMousey(), Maze::getMousex());
//        // char next = next_move(Maze::getMousey(), Maze::getMousex()); 
//        //moveFalcon(next, 0.2);
//        print_maze();
//    }

//    while (state == 2) { // Go Home State

//        if (is_start(encodeCellIndex(Maze::getMousey(), Maze::getMousex()))) {
//            print_maze();
//            getchar();
//            // Do prep for Speed Run
//            speedRunPrep();
//            floodfill();
//            print_maze();
//            state++;
//            continue;
//        }
//        getchar();
//        //cycleMFs(0.02);
//        Maze::updateWalls(Maze::getMousey(), Maze::getMousex());
//        update_distances(Maze::getMousey(), Maze::getMousex());
//        next_move(Maze::getMousey(), Maze::getMousex());
//        //char next = next_move(Maze::getMousey(), Maze::getMousex());
//        //moveFalcon(next, 0.2);
//        print_maze();

//    }

//    while (state == 3) { // Speed Run State
//        getchar();
//        if (is_center(encodeCellIndex(Maze::getMousey(), Maze::getMousex()))) {
//            printf("suck it\n");
//            break;
//        }
//        //cycleMFs(0.02);
//        // Maze::updateWalls(Maze::getMousey(), Maze::getMousex());
//        //update_distances(Maze::getMousey(), Maze::getMousex());
//        next_move(Maze::getMousey(), Maze::getMousex());
//        // char next = next_move(Maze::getMousey(), Maze::getMousex()); 
//        //moveFalcon(next, 0.2);
//        print_maze();

//    }
//     // testBuzzer();
// }



