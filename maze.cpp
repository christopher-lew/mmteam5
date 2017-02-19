#include "maze.h"
#include "math.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>


Cell *maze[MAZE_SIZE][MAZE_SIZE];
Cell *mazeIn[MAZE_SIZE][MAZE_SIZE];

// FUNCTION for mouse direction
//TODO Function for mouse direction

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
int min_open_neighbor(vector<Cell*> cells) {
    int min = UCHAR_MAX;
    for (vector<Cell *>::iterator it = cells.begin(); it != cells.end(); it++) {
        if ((*it)->dist < min) {
            min = (*it)->dist;
        }
    }
    return min;
}

// FUNCTION to initialize the maze
void init_maze() {
    int goal1 = MAZE_SIZE / 2;
    int goal2 = MAZE_SIZE / 2 - 1;
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            maze[i][j] = new Cell(i, j, min4(manhattan_dist(i, goal1, j, goal1),
                                             manhattan_dist(i, goal1, j, goal2),
                                             manhattan_dist(i, goal2, j, goal1),
                                             manhattan_dist(i, goal2, j, goal2)));
            
            if (i == MAZE_SIZE - 1) maze[i][j]->top_wall = true;

            if (j == MAZE_SIZE - 1) maze[i][j]->right_wall = true;
        }
    }
    // Mouse starts at bottom right side maze pointing north
    maze[0][0]->mouse = true;
    maze[0][0]->right_wall = true;
    maze[1][0]->right_wall = true;
    maze[2][0]->right_wall = true;

}

// FUNCTION to check whether the cell is the center cell
bool is_center(Cell *cell) {
  int x = cell->x;
  int y = cell->y;
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
Cell* next_move(Cell *current) {
    int x, y, minx, miny, i, j;
    int x_goal = MAZE_SIZE / 2;
    int y_goal = MAZE_SIZE - 1 / 2;
    // Initial positions of the next move
    minx = 0;
    miny = 0;
    // Initial position of mouse
    x = current->x;
    y = current->y;
    // checks the next cell with the smallest distance
    for(i = -1; i <= 1; i++){
        for(j = -1; j <= 1; j++){
            int next_x = x + i;
            int next_y = y + j;
            // pass over non open right neighbors
            if (current->right_wall == true && next_x == x + 1) continue;
            // pass over non open top neightbors
            if (current->top_wall == true && next_y == y + 1) continue;
            // border cells are ignored
            if(next_x < 0 || next_y < 0)  continue;
            // means cell does not exist
            if(maze[next_x][next_y] == 0) continue;
            // ignore diagonal cells for now
            if((next_x != current->x) && (next_y != current->y))  continue;
            // if the next cell has a smaller distance then check
            if(maze[next_x][next_y]->dist < current->dist){
                // breaking ties
                if((next_x == minx) && (next_y == miny)){
                    // check if the mouse is facing straight 0->1->2->3 counter-clockwise
                   if((current_direction == TOP && next_x > y) || (current_direction == DOWN && next_y < y) ||
                      (current_direction == LEFT && next_x < x) || (current_direction == RIGHT && next_x > x)){
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
                }
            }
            
        }
    }
   // signals next cell's direction
   if((minx < x) && (miny == y)){
       next_direction = LEFT;
   }

   if((minx == x) && (miny > y)){
       next_direction = TOP;
   }

   if((minx > x) && (miny == y)){
       next_direction = RIGHT;
   }

   if((minx == x) && (miny < y)){
       next_direction = DOWN;
   }
    return maze[minx][miny];
}

Cell* next_move(Cell *current) {
    int x, y, minx, miny, i, j;
    int x_goal = MAZE_SIZE / 2;
    int y_goal = MAZE_SIZE - 1 / 2;
    // Initial positions of the next move
    minx = 0;
    miny = 0;
    // Initial position of mouse
    x = current->x;
    y = current->y;

    vector<Cell*> neighbors;

    // check top neighbor
    if (y < MAZE_SIZE - 1) {
        neighbors.push_back(maze[y + 1][x]);
    }
    // check right neighbor
    if (x < MAZE_SIZE - 1) {
        neighbors.push_back(maze[y][x + 1]);
    }
    // check bottom neighbor
    if (y > 0) {
        neighbors.push_back(maze[y - 1][x]);
        if (!maze[y - 1][x]->top_wall) {
            open_neighbors.push_back(maze[y - 1][x]);
        }
    }
    // check left neighbor
    if (x > 0) {
        neighbors.push_back(maze[y][x - 1]);
        if (!maze[y][x - 1]->right_wall) {
            open_neighbors.push_back(maze[y][x - 1]);
        }
    }



}

// FUNCTION to generate walls for the maze
void generate_random_walls() {
    string s;
    srand((unsigned) time(0));
    int numCells = MAZE_SIZE * MAZE_SIZE;
    int numWalls = rand() % (numCells / 4) + (numCells * 3 / 4);
    
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            int y = MAZE_SIZE - 1 - i;
            int type = rand() % 4;
            if (numWalls > 0) {
                if (type == 1) {
                    maze[y][j]->top_wall = true;
                    numWalls--;
                    s += "T_\t";
                }
                else if (type == 2) {
                    maze[y][j]->right_wall = true;
                    numWalls--;
                    s += "_R\t";
                }
                else if (type == 3) {
                    maze[y][j]->top_wall = true;
                    maze[y][j]->right_wall = true;
                    numWalls--;
                    s += "TR\t";
                }
                else {
                    s += "__\t";
                }
            }
            else {
                s += "__\t";
            }
        }
        s += "\n";
    }
}

// FUNCTION to check if the maze has been fully explored
bool fully_explored() {
    for (int y = 0; y < MAZE_SIZE; y++) {
        for (int x = 0; x < MAZE_SIZE; x++) {
            if (maze[y][x] == false) {
                return false;
            }
        }
    }
    return true;
}

// FUNCTION to print maze
void print_maze() {
    
    // print top wall
    for (int i = 0; i < MAZE_SIZE; i++) {
        printf("+---");
    }
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
                if (maze[y][j]->top_wall) {
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
                
                int dist = maze[y][j]->dist;
                if (maze[y][j]->mouse) {
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
                
                if (maze[y][j]->right_wall || j == MAZE_SIZE - 1) {
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
}

// FUNCTION to update the distances
void update_distances(vector <Cell*> &stack) {
    Cell *current;
    vector<Cell*> open_neighbors;
    vector<Cell*> neighbors;
    
    int x, y;
    int min;
    while (!stack.empty()) {
        current = stack.back();
        stack.pop_back();
        x = current->x;
        y = current->y;
        
        if (is_center(current)) {
            continue;
        }
        
        // check top neighbor
        if (y < MAZE_SIZE - 1) {
            neighbors.push_back(maze[y + 1][x]);
            if (!current->top_wall) {
                open_neighbors.push_back(maze[y + 1][x]);
            }
        }
        // check right neighbor
        if (x < MAZE_SIZE - 1) {
            neighbors.push_back(maze[y][x + 1]);
            if (!current->right_wall) {
                open_neighbors.push_back(maze[y][x + 1]);
            }
        }
        // check bottom neighbor
        if (y > 0) {
            neighbors.push_back(maze[y - 1][x]);
            if (!maze[y - 1][x]->top_wall) {
                open_neighbors.push_back(maze[y - 1][x]);
            }
        }
        // check left neighbor
        if (x > 0) {
            neighbors.push_back(maze[y][x - 1]);
            if (!maze[y][x - 1]->right_wall) {
                open_neighbors.push_back(maze[y][x - 1]);
            }
        }
        if (open_neighbors.empty()) {
            neighbors.clear();
            continue;
        }
        min = min_open_neighbor(open_neighbors);
        open_neighbors.clear();
        if (current->dist - 1 != min) {
            current->dist = min + 1;
            for (vector<Cell *>::iterator it = neighbors.begin(); it != neighbors.end(); it++) {
                if (!is_center(*it)) {
                    stack.push_back(*it);
                }
            }
            neighbors.clear();
        }
        
    }
}

/**
 * Explore is the function that runs the micromouse from a given starting
 * position, and a stack, the mouse explores the maze, and actively figures
 * the map of the maze, while finding its way to the goal
 * @param vector<Cell*> &stack to update the distances
 * @param int x, y the position of the micromouse in the maze
 * @return void
 **/ 
 void explore(vector<Cell*> &stack, int y, int x) {
    
    // Print the maze
    print_maze();
    getchar();

    /** 
     * if the cell at position x, y has already been visited,
     * then we don't care want to explore it again
     **/
    if (maze[y][x]->visited) {
        return;
    }
    // else set the cell->visited to true
    else maze[y][x]->visited = true;

    /** 
     * If micromouse encounters a wall, then push the cell onto the
     * stack and update the distances
     **/
    if (maze[y][x]->top_wall || maze[y][x]->right_wall) {
        stack.push_back(maze[y][x]);
        update_distances(stack);
        explore(stack, y, x);
    }

    // Generate the next move based on the distances, and explore
    Cell* next_cell = next_move(maze[y][x]);
    maze[y][x]->mouse = false;
    next_cell->mouse = true;
    explore(stack, next_cell->y, next_cell->x);


 }


// void explore(vector<Cell*> &stack, int y, int x) {
//     if (maze[y][x]->visited) {
//         return;
//     }
//     else {
//         maze[y][x]->visited = true;
//         //set_wall(y,x);
//     }
//     if (maze[y][x]->top_wall || maze[y][x]->right_wall) {
//         stack.push_back(maze[y][x]);
//         update_distances(stack);
//     }
//     // if mouse is located bottom left of center then we want to prioritize exploring top/right
//     if (y < MAZE_SIZE / 2 && x < MAZE_SIZE / 2) {
//         // explore top
//         if (y < MAZE_SIZE - 1) {
//             explore(stack, y + 1, x);
//         }
//         // explore right
//         if (x < MAZE_SIZE - 1) {
//             explore(stack, y, x + 1);
//         }
//         // explore down
//         if (y > 0) {
//             explore(stack, y - 1, x);
//         }
//         // explore left
//         if (x > 0) {
//             explore(stack, y, x - 1);
//         }
//     }
//     // if mouse is located top left of center then we want to prioritize exploring bottom/right
//     else if (y > MAZE_SIZE / 2 && x < MAZE_SIZE / 2) {
//         // explore right
//         if (x < MAZE_SIZE - 1) {
//             explore(stack, y, x + 1);
//         }
//         // explore down
//         if (y > 0) {
//             explore(stack, y - 1, x);
//         }
//         // explore top
//         if (y < MAZE_SIZE - 1) {
//             explore(stack, y + 1, x);
//         }
//         // explore left
//         if (x > 0) {
//             explore(stack, y, x - 1);
//         }
//     }
//     // if mouse is located top right of center then we want to prioritize exploring bottom/left
//     else if (y > MAZE_SIZE / 2 && x > MAZE_SIZE / 2) {
//         // explore down
//         if (y > 0) {
//             explore(stack, y - 1, x);
//         }
//         // explore left
//         if (x > 0) {
//             explore(stack, y, x - 1);
//         }
//         // explore top
//         if (y < MAZE_SIZE - 1) {
//             explore(stack, y + 1, x);
//         }
//         // explore right
//         if (x < MAZE_SIZE - 1) {
//             explore(stack, y, x + 1);
//         }
//     }
//     // if mouse is located bottom right of center then we want to prioritize exploring bottom/right
//     else if (y < MAZE_SIZE / 2 && x > MAZE_SIZE / 2) {
//         // explore left
//         if (x > 0) {
//             explore(stack, y, x - 1);
//         }
//         // explore top
//         if (y < MAZE_SIZE - 1) {
//             explore(stack, y + 1, x);
//         }
//         // explore down
//         if (y > 0) {
//             explore(stack, y - 1, x);
//         }
//         // explore right
//         if (x < MAZE_SIZE - 1) {
//             explore(stack, y, x + 1);
//         }
//     }
// }