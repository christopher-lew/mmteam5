#ifndef MAZE_ENCODING_H
#define MAZE_ENCODING_H

namespace MazeEncoding {

	const unsigned MAZE_SIZE = 16;

	// Encoding for the maze in column major order. Walls represent 4 LSB, where
	// 0001 = W, 0010 = S, 0100 = E, 1000 = N, where 1 represents bit that direction
	unsigned char maze[MAZE_SIZE][MAZE_SIZE] = 
		{
			{ 112, 104, 96, 88, 80, 72, 64, 56, 56, 64, 72, 80, 88, 96, 104, 112 },
			{ 104, 96,  88, 80, 72, 64, 56, 48, 48, 56, 64, 72, 80, 88, 96,  104 },
			{ 96,  88,  80, 72, 64, 56, 48, 40, 40, 48, 56, 64, 72, 80, 88,  96 },
			{ 88,  80,  72, 64, 56, 48, 40, 32, 32, 40, 48, 56, 64, 72, 80,  88 },
			{ 80,  72,  64, 56, 48, 40, 32, 24, 24, 32, 40, 48, 56, 64, 72,  80 },
			{ 72,  64,  56, 48, 40, 32, 24, 16, 16, 24, 32, 40, 48, 56, 64,  72 },
			{ 64,  56,  48, 40, 32, 24, 16, 8,  8,  16, 24, 32, 40, 48, 56,  64 },
			{ 56,  48,  40, 32, 24, 16,  8, 0,  0,  8,  16, 24, 32, 40, 48,  56 },
			{ 56,  48,  40, 32, 24, 16,  8, 0,  0,  8,  16, 24, 32, 40, 48,  56 },
			{ 64,  56,  48, 40, 32, 24, 16, 8,  8,  16, 24, 32, 40, 48, 56,  64 },
			{ 72,  64,  56, 48, 40, 32, 24, 16, 16, 24, 32, 40, 48, 56, 64,  72 },
			{ 80,  72,  64, 56, 48, 40, 32, 24, 24, 32, 40, 48, 56, 64, 72,  80 },
			{ 88,  80,  72, 64, 56, 48, 40, 32, 32, 40, 48, 56, 64, 72, 80,  88 },
			{ 96,  88,  80, 72, 64, 56, 48, 40, 40, 48, 56, 64, 72, 80, 88,  96 },
			{ 104, 96,  88, 80, 72, 64, 56, 48, 48, 56, 64, 72, 80, 88, 96,  104 },
			{ 112, 104, 96, 88, 80, 72, 64, 56, 56, 64, 72, 80, 88, 96, 104, 112 },

		}

	// Return the 4 LSB by pushing the bits that represent distance off, then bringing them back to LSB
	inline unsigned char decodeWalls (int y, int x) {
		unsigned char cell = maze[y][x];
		return cell << 12 >> 12;
	}

	// Return the 12 MSB by pushing the bits that represent walls off
	inline unsigned char decodeDist (int y, int x) {
		unsigned char cell = maze[y][x];
		return cell >> 4;
	}

	// Update the walls using AND operator
	inline void encodeWalls (int y, int x, unsigned char newWall) {
		// Save the dist in a temporary mask
		unsigned char dist = decodeDist(y,x);

		dist = dist << 4;

		// Set the new wall to the maze index with dist using OR operator
		maze[y][x] = dist | newWall;
	}

	// Update the distance using the AND operator
	inline void encodeDist (int y, int x, unsigned char newDist) {
		// Save the walls in a temporary mask
		unsigned char walls = decodeWalls(y, x);

		newDist = newDist << 4;

		// Set the newDist to the maze index with walls using OR operator
		maze[y][x] = newDist | walls;
		
	}

	// Function to reset the maze
	void reset () {
		maze = 		
		{   { 112, 104, 96, 88, 80, 72, 64, 56, 56, 64, 72, 80, 88, 96, 104, 112 },
			{ 104, 96,  88, 80, 72, 64, 56, 48, 48, 56, 64, 72, 80, 88, 96,  104 },
			{ 96,  88,  80, 72, 64, 56, 48, 40, 40, 48, 56, 64, 72, 80, 88,  96 },
			{ 88,  80,  72, 64, 56, 48, 40, 32, 32, 40, 48, 56, 64, 72, 80,  88 },
			{ 80,  72,  64, 56, 48, 40, 32, 24, 24, 32, 40, 48, 56, 64, 72,  80 },
			{ 72,  64,  56, 48, 40, 32, 24, 16, 16, 24, 32, 40, 48, 56, 64,  72 },
			{ 64,  56,  48, 40, 32, 24, 16, 8,  8,  16, 24, 32, 40, 48, 56,  64 },
			{ 56,  48,  40, 32, 24, 16,  8, 0,  0,  8,  16, 24, 32, 40, 48,  56 },
			{ 56,  48,  40, 32, 24, 16,  8, 0,  0,  8,  16, 24, 32, 40, 48,  56 },
			{ 64,  56,  48, 40, 32, 24, 16, 8,  8,  16, 24, 32, 40, 48, 56,  64 },
			{ 72,  64,  56, 48, 40, 32, 24, 16, 16, 24, 32, 40, 48, 56, 64,  72 },
			{ 80,  72,  64, 56, 48, 40, 32, 24, 24, 32, 40, 48, 56, 64, 72,  80 },
			{ 88,  80,  72, 64, 56, 48, 40, 32, 32, 40, 48, 56, 64, 72, 80,  88 },
			{ 96,  88,  80, 72, 64, 56, 48, 40, 40, 48, 56, 64, 72, 80, 88,  96 },
			{ 104, 96,  88, 80, 72, 64, 56, 48, 48, 56, 64, 72, 80, 88, 96,  104 },
			{ 112, 104, 96, 88, 80, 72, 64, 56, 56, 64, 72, 80, 88, 96, 104, 112 },

		}
	}
}