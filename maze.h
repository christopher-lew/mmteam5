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

#define TOP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

using namespace std;

const int MAZE_SIZE = 4;

extern int next_cell_direction;
extern int direction;
extern bool has_right_wall;
extern bool has_left_wall;
extern int current_direction;
extern int next_direction;
extern int drive_distance;

/**
 * Cell inner class for the maze
 */
class Cell {
    
public:
    int y;
    int x;
    int dist;
    bool top_wall;
    bool right_wall;
    bool visited;
    bool mouse;
    
    Cell(int y, int x) : y(y), x(x), dist(0), top_wall(false), right_wall(false) {}
    Cell(int y, int x, int dist) : y(y), x(x), dist(dist), top_wall(false), right_wall(false) {}
    Cell(int y, int x, bool top_wall, bool right_wall) : y(y), x(x), top_wall(top_wall), right_wall(right_wall) {}
};


extern Cell *maze[MAZE_SIZE][MAZE_SIZE];
extern Cell *mazeIn[MAZE_SIZE][MAZE_SIZE];

vector<Cell*> get_open_neighbors(int y, int x, Cell* current);

int manhattan_dist(int x1, int x2, int y1, int y2);

int min4(int a, int b, int c, int d);

void update_distances(vector<Cell*> &stack);

bool fully_explored();

void explore(vector<Cell*> &stack, int y, int x);

bool is_solved();

void generate_random_walls();

void init_maze();

void print_maze();

bool is_center(Cell* cell);

void set_wall(int y,int x);

Cell* next_move(Cell* cell);

void print_maze();


#endif
