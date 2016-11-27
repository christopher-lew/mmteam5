/**
 * Cell class header file
 */

#ifndef __CELL_H__
#define __CELL_H__

/**
 * @author Christopher Lew
 * @version 0.1
 */

using namespace std;

class Cell {

public:
// -------- CELL DATA -------- //
  int x; // x coordinate
  int y; // y coordinate
  int dist; // distance from center

  bool top_wall; // Flag if cell has a top_wall
  bool right_wall; // Flag if cell has a right_wall
  bool left_wall; // Flag if cell has a left_wall
  bool bot_wall; // Flag if cell has a bot_wall

  bool visited; // Flag if cell is visited
// -------- CELL DATA -------- //

  // -------- CONSTRUCTORS -------- //
  Cell (int x, int y) : y(y), x(x), dist(0), top_wall(false), right_wall(false), left_wall(false), bot_wall(false) {}
  Cell (int x, int y, int dist) : y(y), x(x), dist(dist), top_wall(false), right_wall(false), left_wall(false), bot_wall(false) {}
  Cell (int x, int y, bool top_wall, bool right_wall, bool left_wall, bool bot_wall) : y(y), x(x), dist(0), top_wall(top_wall), right_wall(right_wall), left_wall(left_wall), bot_wall(bot_wall) {}

  // -------- CONSTRUCTORS -------- //
  // FUNCTION to set the TRUE distance of the cell from the center
  int set_distance(int x1, int x2, int y1, int y2);

  // FUNCTION to get the TRUE distance of the cell from the center
  int get_distance();

  // FUNCTION to set the flags of the wall from an int (0 = top_wall, 1 = right_wall
  // 2 = left_wall, 3 = bot_wall) returns true if set_wall succeeds
  bool set_wall(int wall);

private:
  int manhatten_dist(int x1, int x2, int y1, int y2);

}

#endif
