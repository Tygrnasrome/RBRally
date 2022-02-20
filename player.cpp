#include "player.h"

Player::Player(int x, int y, int tile_num)
{
	this->x = x;
	this->y = y;
	standingPos = revivePos = tile_num;
	red = g = b = 200;
	facing = NORTH;
}

void Player::draw()
{

	int j;
	int r = 20;
	barva(red,g,b);

	for (int i = 0 ; i < r ; i++)
	{
		j = sqrt(r * r - i * i);

		bod (x + i, y-j);
		cara (x + i, y + j);

		bod (x - i, y-j);
		cara (x - i, y + j);
	}
	barva(red-10,g-10,b-10);

	if (facing == NORTH)
	{
		for (int i = 0 ; i < r ; i++)
		{
			bod(x-r/2+i,y);
			cara(x,y-25);

			barva(CERNA);
			bod(x-r/2,y);
			cara(x,y-25);
			cara(x+r/2,y);
			cara(x-r/2,y);
		}
	}
	if (facing == SOUTH)
	{
		for (int i = 0 ; i < r ; i++)
		{
			bod(x-r/2+i,y);
			cara(x,y+25);

			barva(CERNA);
			bod(x-r/2,y);
			cara(x,y+25);
			cara(x+r/2,y);
			cara(x-r/2,y);
		}
	}
	if (facing == EAST)
	{
		for (int i = 0 ; i < r ; i++)
		{
			bod(x,y-r/2+i);
			cara(x+25, y);

			barva(CERNA);
			bod(x,y-r/2);
			cara(x+25,y);
			cara(x, y+r/2);
			cara(x, y-r/2);
		}
	}
	if (facing == WEST)
	{
		for (int i = 0 ; i < r ; i++)
		{
			bod(x,y-r/2+i);
			cara(x-25, y);

			barva(CERNA);
			bod(x,y-r/2);
			cara(x-25,y);
			cara(x, y+r/2);
			cara(x, y-r/2);
		}
	}


}
void Player::update(int x, int y)
{
	this->x = x;
	this->y = y;
}

