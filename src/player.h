#ifndef PLAYER_H
#define PLAYER_H

#include "grafika.h"
#include "math.h"
#include "map.h"
#include "register.h"


#include <array>

class Map;
class Register;
class Player
{
public:
	Player(int x, int y, int tile_num);
	int x, y, red, g, b, revivePos, standingPos, health, damage, damageMax;
	std::array<Register*,5> registers;
	void draw();
	void update(int x, int y);
	void move(int move, Map *map);

	void rotate(int rotation);
	bool shoot(Map *map);
	bool revive();
	void takeDamage();
	bool testDamage();



	typedef enum{
		NORTH,
		EAST,
		SOUTH,
		WEST

	}Facing;
	Facing facing;
	void boardMove(int move, Map *map, int tileFacing);
	bool dead = false;
	bool interrupted = false;
	bool commenceShutdown = false;
	bool shutdown = false;
	bool move(int mov, Map *map, Facing tmpFacing);
private:
	bool testWallCollision(int move, Map *map, int type);
	bool testMapEnd(int move, Map *map);
	bool testPlayerCollision(int move, Map *map);
	void PlayerCollision(int move, Map *map);

};

#endif // PLAYER_H
