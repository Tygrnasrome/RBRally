#ifndef PLAYER_H
#define PLAYER_H

#include "grafika.h"
#include "math.h"
#include "map.h"
class Map;
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



	typedef enum{
		NORTH,
		EAST,
		SOUTH,
		WEST

	}Facing;
	Facing facing;

	bool dead = false;
	bool interrupted = false;
	bool move(int mov, Map *map, Facing tmpFacing);
private:
	void testWallCollision(int move, Map *map);
	void testMapEnd(int move, Map *map);
	bool testPlayerCollision(int move, Map *map);
	void PlayerCollision(int move, Map *map);

};

#endif // PLAYER_H
