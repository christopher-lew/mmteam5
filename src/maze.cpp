#include "maze.h"

#include <stdio.h>
#include <stdlib.h>

Maze::Dir Maze::current_direction = Maze::NORTH;

// Initialize static member of maze
unsigned char Maze::the_maze[MAZE_SIZE][MAZE_SIZE] =  {
            { 224, 208, 192, 176, 160, 144, 128, 112, 112, 128, 144, 160, 176, 192, 208, 224 },
            { 208, 192, 176, 160, 144, 128, 112,  96,  96, 112, 128, 144, 160, 176, 192, 208 },
            { 192, 176, 160, 144, 128, 112,  96,  80,  80,  96, 112, 128, 144, 160, 176, 192 },
            { 176, 160, 144, 128, 112,  96,  80,  64,  64,  80,  96, 112, 128, 144, 160, 176 },
            { 160, 144, 128, 112,  96,  80,  64,  48,  48,  64,  80,  96, 112, 128, 144, 160 },
            { 144, 128, 112,  96,  80,  64,  48,  32,  32,  48,  64,  80,  96, 112, 128, 144 },
            { 128, 112,  96,  80,  64,  48,  32,  16,  16,  32,  48,  64,  80,  96, 112, 128 },
            { 112,  96,  80,  64,  48,  32,  16,   0,   0,  16,  32,  48,  64,  80,  96, 112 },
            { 112,  96,  80,  64,  48,  32,  16,   0,   0,  16,  32,  48,  64,  80,  96, 112 },
            { 128, 112,  96,  80,  64,  48,  32,  16,  16,  32,  48,  64,  80,  96, 112, 128 },
            { 144, 128, 112,  96,  80,  64,  48,  32,  32,  48,  64,  80,  96, 112, 128, 144 },
            { 160, 144, 128, 112,  96,  80,  64,  48,  48,  64,  80,  96, 112, 128, 144, 160 },
            { 176, 160, 144, 128, 112,  96,  80,  64,  64,  80,  96, 112, 128, 144, 160, 176 },
            { 192, 176, 160, 144, 128, 112,  96,  80,  80,  96, 112, 128, 144, 160, 176, 192 },
            { 208, 192, 176, 160, 144, 128, 112,  96,  96, 112, 128, 144, 160, 176, 192, 208 },
            { 224, 208, 192, 176, 160, 144, 128, 112, 112, 128, 144, 160, 176, 192, 208, 224 },

};

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


// FUNCTION to grab the minimum neighbor of the
int min_open_neighbor(vector<unsigned char> cells) {
    int min = UCHAR_MAX;
    for (vector<unsigned char>::iterator it = cells.begin(); it != cells.end(); it++) {
        
        // Get the indices of the encoded index
        int y = decodeYIndex(*it);
        int x = decodeXIndex(*it);

        // Check if distance of cell is less than min
        if (Maze::decodeDist(y, x) < min) {
            min = Maze::decodeDist(y, x);
        }
    }
    return min;
}

// FUNCTION to check whether the mouse is at the center cell
bool is_center(unsigned char cell) { // cell is encoded index
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
unsigned char next_move(int currX, int currY) { // (Maze::Cell *current)
    int x, y, minx, miny, i, j;
    int x_goal = MAZE_SIZE / 2;
    int y_goal = MAZE_SIZE - 1 / 2;
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
            // pass over non open right neighbors
            if (Maze::has_right_wall(y, x) == true && next_x == x + 1) continue;
            // pass over non open top neightbors
            if (Maze::has_top_wall(y, x) == true && next_y == y + 1) continue;
            // border cells are ignored
            if(next_x < 0 || next_y < 0)  continue;
            // means cell does not exist
            if(next_y < 0 || next_y >= MAZE_SIZE || next_x < 0 || next_x >= MAZE_SIZE) continue;
            // ignore diagonal cells for now
            if((next_x != Maze::getMousex()) && (next_y != Maze::getMousey()))  continue;
            // if the next cell has a smaller distance then check
            if(Maze::decodeDist(next_y,next_x) < Maze::decodeDist(y, x)){
                // breaking ties
                if((next_x == minx) && (next_y == miny)){
                    // check if the mouse is facing straight 0->1->2->3 counter-clockwise
                   if((Maze::current_direction == Maze::NORTH && next_x > y) || (Maze::current_direction == Maze::SOUTH && next_y < y) ||
                      (Maze::current_direction == Maze::WEST && next_x < x) || (Maze::current_direction == Maze::EAST && next_x > x)){
                       minx = x + i;
                       miny = y + j;
                       continue;
                   }
                    //check for whichever is closer to the center of the maze
                   else{
                       double prev_to_goal = sqrt(pow(x_goal - minx, 2.0) + pow(y_goal - miny, 2.0));
                       double curr_to_goal = sqrt(pow(x_goal - next_x, 2.0) + pow(y_goal - next_y, 2.0));
                       if(curr_to_goal < prev_to_goal){
                           minx = x + i;
                           miny = y + j;
                           continue;
                       }
                   }
                }
                else{
                    // not tie condition
                    minx = x + i;
                    miny = y + j;
                    cout << "minx = " << minx << endl;
                    cout << "miny = " << miny << endl;
                }
            }
            
        }
    }
  // signals next cell's direction
  if((minx < x) && (miny == y)){
      Maze::current_direction = Maze::WEST;
  }

  if((minx == x) && (miny > y)){
      Maze::current_direction = Maze::NORTH;
  }

  if((minx > x) && (miny == y)){
      Maze::current_direction = Maze::EAST;
  }

  if((minx == x) && (miny < y)){
      Maze::current_direction = Maze::SOUTH;
  }
   

    // Returns cell to be moved to
    return encodeCellIndex(miny, minx);
}

// // FUNCTION to check if the maze has been fully explored
// bool fully_explored() {
//     for (int y = 0; y < MAZE_SIZE; y++) {
//         for (int x = 0; x < MAZE_SIZE; x++) {
//             if (maze[y][x]->visited == false) {
//                 return false;
//             }
//         }
//     }
//     return true;
// }

// FUNCTION to update the distances
void update_distances(vector <unsigned char> &stack) {
    unsigned char current;
    vector<unsigned char> open_neighbors;
    vector<unsigned char> neighbors;
    
    int x, y;
    int min;
    while (!stack.empty()) {
        current = stack.back();
        stack.pop_back();

        x = decodeXIndex(current);
        y = decodeYIndex(current);
        
        if (is_center(current)) {
            continue;
        }
        
        // check top neighbor
        if (y < MAZE_SIZE - 1) {
            neighbors.push_back(current);
            if (!Maze::has_top_wall(y, x)) {
                open_neighbors.push_back(current);
            }
        }
        // check right neighbor
        if (x < MAZE_SIZE - 1) {
            neighbors.push_back(current);
            if (!Maze::has_right_wall(y, x)) {
                open_neighbors.push_back(current);
            }
        }
        // check bottom neighbor
        if (y > 0) {
            neighbors.push_back(current);
            if (!Maze::has_top_wall(y - 1, x)) {
                open_neighbors.push_back(current);
            }
        }
        // check left neighbor
        if (x > 0) {
            neighbors.push_back(current);
            if (!Maze::has_right_wall(y, x - 1)) {
                open_neighbors.push_back(current);
            }
        }
        if (open_neighbors.empty()) {
            neighbors.clear();
            continue;
        }
        min = min_open_neighbor(open_neighbors);
        open_neighbors.clear();
        if (Maze::decodeDist(y, x) - 1 != min) {
            Maze::encodeDist(y, x, (unsigned char) min + 1);
            for (vector<unsigned char>::iterator it = neighbors.begin(); it != neighbors.end(); it++) {
                if (!is_center(*it)) {
                    stack.push_back(*it);
                }
            }
            neighbors.clear();
        }
        
    }
}

// FUNCTION to explore the cells
void explore(vector<unsigned char> &stack, int y, int x) {

    if (is_center(encodeCellIndex(y, x))) {
        return;
    }
    // Print the maze
    print_maze();

    getchar();
    // /** 
    //  * if the cell at position x, y has already been visited,
    //  * then we don't care want to explore it again
    //  **/
    // if (maze[y][x]->visited) {
    //     return;
    // }
    // // else set the cell->visited to true
    // else maze[y][x]->visited = true;

    // * 
    //  * If micromouse encounters a wall, then push the cell onto the
    //  * stack and update the distances
    //  *
    cout << Maze::has_top_wall(y, x) << endl;
    cout << Maze::has_right_wall(y, x) << endl;

    if (Maze::has_top_wall(y, x) || Maze::has_right_wall(y, x)) {
        stack.push_back(encodeCellIndex(y, x));
        update_distances(stack);
        explore(stack, y, x);
    }

    // Generate the next move's encoded index based on the distances, and explore
    unsigned char next_cell = next_move(Maze::getMousey(), Maze::getMousex());

    cout << "next_cell =" << next_cell << endl;

    // Decode the cell indices
    int next_y = decodeYIndex(next_cell);
    int next_x = decodeXIndex(next_cell);

    // Update the mouse position
    Maze::setMousex(next_x);
    Maze::setMousey(next_y);

    explore(stack, Maze::getMousey(), Maze::getMousex());


}

// FUNCTION to print maze
void print_maze() {
    
    // print top wall
    for (int i = 0; i < 16; i++) {
        //pc.printf("+---");
        printf("+---");
    }
//    pc.printf("+\n");
    printf("+\n");
    
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
                if (Maze::decodeWalls(y, j) >> 3 == 1) {
//                    pc.printf("+---");
                    printf("+---");
                }
                else {
//                    pc.printf("+   ");
                    printf("+   ");
                }
                if (j == MAZE_SIZE - 1) {
//                    pc.printf("+");
                    printf("+");
                }
            }
            
            else {
                if (j == 0) {
//                    pc.printf("|");
                    printf("|");
                }
                
                int dist = (int) Maze::decodeDist(y, j);
                if (y == Maze::getMousey() && j == Maze::getMousex()) {
                    printf(" M ");

                }
                // else if (maze[y][j]->visited) {
                //     printf(" * ");
                // }
                else if (dist > 99) {
//                    pc.printf("%d", dist);
                    printf("%d", dist);
                }
                else if (dist > 9) {
//                    pc.printf(" %d", dist);
                    printf(" %d", dist);
                }
                else {
//                    pc.printf(" %d ", dist);
                    printf(" %d ", dist);
                }
                
                if ((Maze::decodeWalls(y, j) << 13 >> 15) == 1 || j == MAZE_SIZE - 1) {
//                    pc.printf("|");
                    printf("|");
                }
                else {
//                    pc.printf(" ");
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    
    // print bottom wall
    for (int i = 0; i < MAZE_SIZE; i++) {
//        pc.printf("+---");
        printf("+---");
    }
//    pc.printf("+\n\n End Print Function\n");
    printf("+\n\n");
    
    cout << "End Print Function" << endl;
}

// Return an int value representing an index in maze as 1 int
    unsigned char encodeCellIndex(int y, int x) {
        y = y << 5;
        unsigned char encodedVal = y | x;
        cout << "encoded value = " << encodedVal << endl;
        return encodedVal; // 10 LSB matters: Y is in 5 MSB, X in 5 LSB. 6 MSB are DONT CARES
    }

    // Return an x value from encoded index
    int decodeXIndex(unsigned char encodedIndex) {
        return  (int) encodedIndex & 31; // Will return the x index of encoded index via mask 0000011111
    }

    // Return a y value from encoded index
    int decodeYIndex(unsigned char encodedIndex) {
        return (int) encodedIndex & 992; // Will return y index of encoded index via mask 1111100000
    }

