//#include "mbed.h"
//#include "initSensors.hpp"
#include "maze.h"

#include <iostream> // Use pc instead of std?
//#include "debug_io.hpp" // Uncomment if debugging

int main()
{
    //std::cout << "testing" << std::endl;
    init_maze();
    print_maze();
        
}
