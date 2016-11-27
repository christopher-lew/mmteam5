/**
 * Maze class header file
 */

#ifndef __MAZE_H__
#define __MAZE_H__

/**
 * @author Christopher Lew
 * @version 0.1
 */

using namespace std;

const int MAZE_SIZE = 8;

/**
 * Psuedocode: A matrix of cells
 * CLASS MAZE:
 * In : maze(int[][]), x(int x), y(int y), direction(int dir)
 */
class Maze {

public:
  Cell *maze[][]

private:

// FUNCTION to check whether the cell is the center cell
bool is_center(Cell *cell) {
  int x = cell->x;
  int y = cell->y;
  int goal1 = MAZE_SIZE / 2;
  int goal2 = (MAZE_SIZE - 1) / 2;

  // Checks if the manhattan_dist of the current cell to the 4 goal states is 0
  if (cell.manhattan_dist(y, goal1, x, goal1) == 0 ||
      cell.manhattan_dist(y, goal1, x, goal2) == 0 ||
      cell.manhattan_dist(y, goal2, x, goal1) == 0 ||
      cell.manhattan_dist(y, goal2, x, goal2) == 0)
      // If so, return TRUE
      { return true; }
  // Else, not the center, return false
  return false;

}

void print_maze();

}

#endif
