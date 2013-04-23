#ifndef GLOBAL_H
#define GLOBAL_H

const short MAZE_SIZE = 20;
const short TILE_SIZE = 20;

enum CELL_STATE {
	ST_EMPTY = 1,
	ST_BALL = 5,
	ST_WALL = 0,
	ST_PERM_WALL = 8,
	ST_FINISH = 6
};

enum PRESSED_KEY {
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT
};

struct coordinate
{
	short int x; // the x coordinate
	short int y; // the y coordinate
};

#endif