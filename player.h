#ifndef PLAYER_H
#define PLAYER_H

#include "grafika.h"
#include "math.h"
#include "map.h"

class Player
{
public:
	Player(int x, int y, int tile_num);
	int x, y, rotation, red, g, b, revivePos, standingPos;

	void draw();
	void update(int x, int y);
	void move(int move, Map *map);
	void rotate();
	void shoot();

	void testWallCollision(int move, Map *map);
	void testMapEnd(int move, Map *map);

	typedef enum{
		NORTH,
		EAST,
		SOUTH,
		WEST

	}Facing;
	Facing facing;

	bool dead = false;
	bool interrupted = false;
};

#endif // PLAYER_H
