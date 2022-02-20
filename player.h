#ifndef PLAYER_H
#define PLAYER_H

#include "grafika.h"
#include "math.h"

class Player
{
public:
	Player(int x, int y, int tile_num);
	int x, y, rotation, red, g, b, revivePos, standingPos;

	void draw();
	void update(int x, int y);
	void move();
	void rotate();
	void shoot();

	typedef enum{
		NORTH,
		EAST,
		SOUTH,
		WEST

	}Facing;
	Facing facing;
};

#endif // PLAYER_H
