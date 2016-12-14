#include "ir.hpp"

/*
 * Constructor for IRController. Initializes IRPairs.
 */
IRController::IRController()
{
	
}

/*
 * Gets the distance to the wall in the direction specified.
 * Param: 
 *	dir - direction of the wall in query
 * Returns:
 *	dist - calculated distance in cm to the wall in direction dir
 */
float IRController::dist_to_wall(char dir)
{
	// N,S,E,W are all relative, with N being the direction the mouse faces
	switch(dir) {
		case 'N': //TODO
			break;
		case 'W': //TODO
			break;
		case 'E': //TODO
			break;
		//DETERMINE IF EXTRA DIAGONAL CASES ARE NEEDED
		default: //TODO handleError() or IRController::setFlag()
			break;
	}
	return 0.0;
}

int main()
{
	return 1;
}