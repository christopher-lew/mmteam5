#include "maze.h"

#include <stdio.h>
#include <stdlib.h>

// 

Dir Maze::current_direction = NORTH;

// // Initialize static member of maze
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

// Test 3x3 Maze
unsigned char Maze::the_maze[3][3] = {
    { 32, 16, 32 },
    { 16, 0 , 16 },
    { 32, 16, 32 },

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
char next_move(int currX, int currY) { // (Maze::Cell *current)
    int x, y, minx, miny, i, j;
    int x_goal = MAZE_SIZE / 2;
    int y_goal = MAZE_SIZE - 1 / 2;

    Dir currDir = Maze::getCurrentDirection();
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
                   if((currDir == NORTH && next_x > y) || (currDir == SOUTH && next_y < y) ||
                      (currDir == WEST && next_x < x) || (currDir == EAST && next_x > x)){
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

    // Update the mouse position
    // Maze::setMousex(min_x);
    // Maze::setMousey(min_y);

    Dir turning = NVALID;

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
    else if((minx == x) && (miny < y)){
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

    return 'F'; // Should never reach, but choooses to go forward lawls.
}

// FUNCTION to get open neighbors of given cell index, and return minimum value
int getMinOfNeighbors(int y, int x) {

    int min = 2000;

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
        if (!Maze::has_top_wall(y - 1, x) && bottomNeighbor < min) {
            min = bottomNeighbor;
        }

    }
    // check left neighbor
    if (x > 0) {
        int leftNeightbor = Maze::decodeDist(y, x - 1);
        if (!Maze::has_right_wall(y, x - 1) && leftNeightbor < min) {
            min = leftNeightbor;
        }
    }

    return min;
    // if return value is 2000, cell is unreachable and has no open neighbors

}
// FUNCTION to update the distances.
void update_distances() {

    /** Function Info
     * Function pushes current position onto the stack.
     * While stack is not empty, pop the top, then find the minimum value of open neighbors
     * 
     * Get the minimum distance value, this represents the direction we would want to move to because it is open,
     * so it should represent the next best move to the center at that point in the algorithm.
     * 
     * If currVal is not exactly 1 more than min value, make curr value 1 greater than min.
     */

    // Initial x, y values
    int x, y;
    x = Maze::getMousex();
    y = Maze::getMousey();

    // Stack to update the distances, and push current cell onto stack
    vector <unsigned char> &stack;
    stack.push_back(encodeCellIndex(y, x));

    // Reference to the current cell
    unsigned char current;

    while (!stack.empty()) {

        current = stack.back();
        stack.pop_back();

        x = decodeXIndex(current);
        y = decodeYIndex(current);

        currentDist = decodeDist(y, x);
        
        // Find the minimum distance value of all the open neighbors of current cell
        min = getMinOfNeighbors(y, x)

        // This means that the current cell is unreachable, so continue WHO CARES ABOUT IT LOLOLOL
        if (min == 2000) continue;

        // Check if min value is exactly 1 less than current value, if not, it means that it is less than min
        if (min + 1 != currentDist) {

            Maze::encodeDist(y, x, (unsigned char) min + 1); // Since it is less than min, make it 1 greater than min

            // Pushback all the neighbors again to the stack
            stack.push_back(encodeCellIndex(y + 1, x)); // Top neighbor
            stack.push_back(encodeCellIndex(y - 1, x)); // Bottom Neighbor
            stack.push_back(encodeCellIndex(y, x + 1)); // Right Neighbor
            stack.push_back(encodeCellIndex(y, x - 1)); // Left Neighbor
        }
    }

}

// FUNCTION to update the walls
void updateWalls() {

    bool leftWall =         leftIR.adjWall(); 
    if (leftWall) Maze::updateWalls(Maze::getMousey(), Maze::getMousex(), 1);

    bool rightWall =        rightIR.adjWall();
    if (rightWall) Maze::updateWalls(Maze::getMousey(), Maze::getMousex(), 100);

    bool frontLeftWall =    frontLeftIR.adjWall();
    bool frontRightWall =   frontRightIR.adjWall();
    if (frontLeftWall && frontRightWall) Maze::updateWalls(Maze::getMousey(), Maze::getMousex(), 1000);

}

// FUNCTION to print maze
void print_maze() {
    
    // print top wall
    for (int i = 0; i < 16; i++) {
        printf("+---");
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
                // else if (maze[y][j]->visited) {
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
                
                if ((Maze::decodeWalls(y, j) << 13 >> 15) == 1 || j == MAZE_SIZE - 1) {
                    printf("|");
                }
                else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    
    // print bottom wall
    for (int i = 0; i < MAZE_SIZE; i++) {
        printf("+---");
    }
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
    return (int) encodedIndex & 992 >> 5; // Will return y index of encoded index via mask 1111100000
}



