#include "player.h"

Player::Player(int x, int y)
{
	revivePos[0] = this->x = x;
	revivePos[1] = this->y = y;
	r = g = b = 200;
}

