CC = g++

FILES = maze.cpp

CFLAGS = -g -Wall $(INC_DIR)

INC_DIR = -I./src/ -I/use/X11/include

all: 
	$(CC) $(CFLAGS) $(INC_DIR) $(FILES) -o micromouse main.cpp






