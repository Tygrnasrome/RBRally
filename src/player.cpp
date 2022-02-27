#include "player.h"

Player::Player(int x, int y, int tile_num)
{
	this->x = x;
	this->y = y;
	standingPos = revivePos = tile_num;
	red = g = b = 200;
	facing = NORTH;
	health = 3;
	damage = 0;
	damageMax = 10;
	for (int i = 0; i<5; i++)
	{
		registers[i] = new Register();
	}
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

void Player::rotate(int rotation)
{
	switch (facing) {
	case NORTH:
		if(rotation == 1)
			facing = EAST;

		if(rotation == -1)
			facing = WEST;
		break;
	case EAST:
		if(rotation == 1)
			facing = SOUTH;

		if(rotation == -1)
			facing = NORTH;
		break;
	case SOUTH:
		if(rotation == 1)
			facing = WEST;

		if(rotation == -1)
			facing = EAST;
		break;
	case WEST:
		if(rotation == 1)
			facing = NORTH;

		if(rotation == -1)
			facing = SOUTH;
		break;
	default:
		break;
	}
}
void Player::boardMove(int move, Map *map, int tileFacing)
{
	switch (tileFacing)
	{
	case 1:
		standingPos -= move*map->map_w;
		break;
	case 3:
		standingPos += move*map->map_w;
		break;
	case 2:
		standingPos += move;
		break;
	case 4:
		standingPos -= move;
		break;
	}
}
void Player::move(int move, Map *map)
{


	interrupted = false;


	if(!testWallCollision(move,map, 0))
		testMapEnd(move,map);
	testWallCollision(move,map, 1);
	if(!interrupted)
		PlayerCollision(move,map);

	switch (facing)
	{
	case NORTH:
		if(!interrupted)
			standingPos -= move*map->map_w;
		break;
	case SOUTH:
		if(!interrupted)
			standingPos += move*map->map_w;
		break;
	case EAST:
		if(!interrupted)
			standingPos += move;
		break;
	case WEST:
		if(!interrupted)
			standingPos -= move;
		break;
	default:
		break;
	}

}

bool Player::testWallCollision(int move, Map *map, int type)
{
	int n = 0;
	switch (facing) {
	case NORTH:
		if (move == 1)
		{
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == standingPos)
					for(int i = 0; i != 4; i++)
					{
						if((*t)->walls[i] == Tile::NORTH)
						{
							interrupted = true;
							return true;
						}
					}
				if(type)
					if(n == standingPos-map->map_w)
						for(int i = 0; i != 4; i++)
						{
							if((*t)->walls[i] == Tile::SOUTH)
							{
								interrupted = true;
								return true;
							}
						}
				n++;
			}
		}



		if (move == -1)
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == standingPos)
					for(int i = 0; i != 4; i++)
					{
						if((*t)->walls[i] == Tile::SOUTH)
						{
							interrupted = true;
							return true;
						}
					}
				if(type)
					if(n == standingPos+map->map_w)
						for(int i = 0; i != 4; i++)
						{
							if((*t)->walls[i] == Tile::NORTH)
							{
								interrupted = true;
								return true;
							}
						}
				n++;
			}
		break;
	case SOUTH:
		if (move == 1)
		{
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == standingPos)
					for(int i = 0; i != 4; i++)
					{
						if((*t)->walls[i] == Tile::SOUTH)
						{
							interrupted = true;
							return true;
						}
					}
				if(type)
					if(n == standingPos+map->map_w)
						for(int i = 0; i != 4; i++)
						{
							if((*t)->walls[i] == Tile::NORTH)
							{
								interrupted = true;
								return true;
							}
						}
				n++;
			}
		}



		if (move == -1)
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == standingPos)
					for(int i = 0; i != 4; i++)
					{
						if((*t)->walls[i] == Tile::NORTH)
						{
							interrupted = true;
							return true;
						}
					}
				if(type)
					if(n == standingPos+map->map_w)
						for(int i = 0; i != 4; i++)
						{
							if((*t)->walls[i] == Tile::SOUTH)
							{
								interrupted = true;
								return true;
							}
						}
				n++;
			}
		break;
	case EAST:
		if (move == 1)
		{
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == standingPos)
					for(int i = 0; i != 4; i++)
					{
						if((*t)->walls[i] == Tile::EAST)
						{
							interrupted = true;
							return true;
						}
					}
				if(type)
					if(n == standingPos+1)
						for(int i = 0; i != 4; i++)
						{
							if((*t)->walls[i] == Tile::WEST)
							{
								interrupted = true;
								return true;
							}
						}
				n++;
			}
		}



		if (move == -1)
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == standingPos)
					for(int i = 0; i != 4; i++)
					{
						if((*t)->walls[i] == Tile::NORTH)
						{
							interrupted = true;
							return true;
						}
					}
				if(type)
					if(n == standingPos+map->map_w)
						for(int i = 0; i != 4; i++)
						{
							if((*t)->walls[i] == Tile::SOUTH)
								interrupted = true;
						}
				n++;
			}
		break;
	case WEST:
		if (move == 1)
		{
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == standingPos)
					for(int i = 0; i != 4; i++)
					{
						if((*t)->walls[i] == Tile::WEST)
						{
							interrupted = true;
							return true;
						}
					}
				if(type)
					if(n == standingPos-1)
						for(int i = 0; i != 4; i++)
						{
							if((*t)->walls[i] == Tile::EAST)
							{
								interrupted = true;
								return true;
							}
						}
				n++;
			}
		}



		if (move == -1)
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == standingPos)
					for(int i = 0; i != 4; i++)
					{
						if((*t)->walls[i] == Tile::NORTH)
						{
							interrupted = true;
							return true;
						}
					}
				if(type)
					if(n == standingPos+map->map_w)
						for(int i = 0; i != 4; i++)
						{
							if((*t)->walls[i] == Tile::SOUTH)
							{
								interrupted = true;
								return true;
							}
						}
				n++;
			}
		break;
	default:
		printf("neplatný enum player facing při wall collision testing");
		break;
	}

}

bool Player::testMapEnd(int move, Map *map)
{
	bool tru = false;
	int h = standingPos/12;
	switch (facing)
	{
	case NORTH:
		if(h == 0 && move == 1 || h == map->map_h-1 && move == -1)
		{
			dead = true;
			interrupted = true;
			tru = true;
			break;
		}
		break;
	case SOUTH:

		if(h == map->map_h-1 && move == 1 || h == 0 && move == -1)
		{
			dead = true;
			interrupted = true;
			tru = true;
			break;
		}
		break;
	case EAST:
		if(standingPos%12 == 11 && move == 1 || standingPos%12 == 0 && move == -1)
		{
			dead = true;
			interrupted = true;
			tru = true;
			break;
		}
		break;
	case WEST:
		if(standingPos%12 == 0 && move == 1 || standingPos%12 == 11 && move == -1)
		{
			dead = true;
			interrupted = true;
			tru = true;
			break;
		}
		break;
	default:
		break;
	}
	return tru;
}

bool Player::testPlayerCollision(int move, Map *map)
{
	int n = 0;
	switch (facing) {
	case NORTH:
		if (move == 1)
		{
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == standingPos-map->map_w)
				{
					if((*t)->occupied != 0)
						return true;
				}
				n++;
			}
		}



		if (move == -1)
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == standingPos+map->map_w)
					if((*t)->occupied != 0)
						return true;
				n++;
			}
		break;
	case SOUTH:
		if (move == 1)
		{
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == standingPos+map->map_w)
					if((*t)->occupied != 0)
						return true;
				n++;
			}
		}



		if (move == -1)
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == standingPos+map->map_w)
					if((*t)->occupied != 0)
						return true;
				n++;
			}
		break;
	case EAST:
		if (move == 1)
		{
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == standingPos+1)
					if((*t)->occupied != 0)
						return true;
				n++;
			}
		}



		if (move == -1)
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == standingPos+map->map_w)
					if((*t)->occupied != 0)
						return true;
				n++;
			}
		break;
	case WEST:
		if (move == 1)
		{
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == standingPos-1)
					if((*t)->occupied != 0)
						return true;
				n++;
			}
		}



		if (move == -1)
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == standingPos+map->map_w)
					if((*t)->occupied != 0)
						return true;
				n++;
			}
		break;
	default:
		printf("neplatný enum player facing při wall collision testing");
		break;
	}

}

void Player::PlayerCollision(int move, Map *map)
{
	int n = 0;
	switch (facing) {
	case NORTH:
		if (move == 1)
		{
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == standingPos-map->map_w)
				{
					if((*t)->occupied != 0)
						if((*t)->occupied->move(move, map, facing))
							interrupted = true;
				}
				n++;
			}
		}



		if (move == -1)
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == standingPos+map->map_w)
					if((*t)->occupied != 0)
						if((*t)->occupied->move(move, map, facing))
							interrupted = true;
				n++;
			}
		break;
	case SOUTH:
		if (move == 1)
		{
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == standingPos+map->map_w)
					if((*t)->occupied != 0)
						if((*t)->occupied->move(move, map, facing))
							interrupted = true;
				n++;
			}
		}



		if (move == -1)
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == standingPos+map->map_w)
					if((*t)->occupied != 0)
						if((*t)->occupied->move(move, map, facing))
							interrupted = true;
				n++;
			}
		break;
	case EAST:
		if (move == 1)
		{
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == standingPos+1)
					if((*t)->occupied != 0)
						if((*t)->occupied->move(move, map, facing))
							interrupted = true;
				n++;
			}
		}



		if (move == -1)
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == standingPos+map->map_w)
					if((*t)->occupied != 0)
						if((*t)->occupied->move(move, map, facing))
							interrupted = true;
				n++;
			}
		break;
	case WEST:
		if (move == 1)
		{
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == standingPos-1)
					if((*t)->occupied != 0)
						if((*t)->occupied->move(move, map, facing))
							interrupted = true;
				n++;
			}
		}



		if (move == -1)
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == standingPos+map->map_w)
					if((*t)->occupied != 0)
						if((*t)->occupied->move(move, map, facing))
							interrupted = true;
				n++;
			}
		break;
	default:
		printf("neplatný enum player facing při wall collision testing");
		break;
	}

}

bool Player::move(int mov, Map *map, Facing tmpFacing)
{
	Facing initFacing;
	initFacing = facing;
	facing = tmpFacing;
	interrupted = false;

	if(!testWallCollision(mov,map, 0))
		if(testMapEnd(mov,map))
		{
			move(mov,map);
			facing = initFacing;
			return false;
		}
	testWallCollision(mov,map, 1);
	if(!interrupted)
		if(testPlayerCollision(mov,map))
		{
			facing = initFacing;
			return true;
		}
	move(mov,map);
	facing = initFacing;
	if(interrupted)
		return true;
	else
		return false;

}

void Player::revive()
{
	if (health>0)
	{
		dead = false;
		standingPos = revivePos;
		facing = NORTH;
		health--;
		damage = 2;
	}

}
bool Player::testDamage()
{
	if(damage == damageMax)
	{
		dead = true;
		return true;
	}else
		return false;
}

void Player::takeDamage()
{
	damage++;
}

bool Player::shoot(Map* map)
{	int dir;
	// init
	switch (facing) {
	case NORTH:
		dir = -map->map_w;
		break;
	case EAST:
		dir = 1;
		break;
	case SOUTH:
		dir = map->map_w;
		break;
	case WEST:
		dir = -1;
		break;
	}
	int tile = standingPos;
	//test
	int h = tile/map->map_w;
	int w = tile%map->map_w;
	int estW = (tile+dir)%map->map_w;
	int n = 0;
	while(1)
	{
		n = 0;
		h = (tile+dir)/map->map_h;
		w =tile%map->map_w;
		estW = (tile+dir)%map->map_w;

		switch (facing) {
		case NORTH:
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == tile)
				{
					if(tile == standingPos)
					for(int i = 0; i != 4; i++)
					{

						if((*t)->walls[i] == Tile::NORTH)
						{
							return true;
						}
					}
					if(tile != standingPos)
					{

						for(int i = 0; i != 4; i++)
						{
							if((*t)->walls[i] == Tile::SOUTH)
							{
								return true;
							}

						}
						(*t)->addBeam(0);
					}
					if(tile != standingPos)
						if((*t)->occupied != nullptr && (*t)->occupied != this)
						{
							(*t)->occupied->takeDamage();
							return true;
						}
					for(int i = 0; i != 4; i++)
					{

						if((*t)->walls[i] == Tile::NORTH)
						{
							return true;
						}
					}


				}
				n++;
			}
			break;
		case EAST:
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == tile)
				{

					if(tile == standingPos)
					for(int i = 0; i != 4; i++)
					{

						if((*t)->walls[i] == Tile::EAST)
						{
							return true;
						}
					}
					if(tile != standingPos)
					{

						for(int i = 0; i != 4; i++)
						{
							if((*t)->walls[i] == Tile::WEST)
							{
								return true;
							}

						}
						(*t)->addBeam(1);
					}
					if(tile != standingPos)
						if((*t)->occupied != nullptr && (*t)->occupied != this)
						{
							(*t)->occupied->takeDamage();
							return true;
						}
					for(int i = 0; i != 4; i++)
					{

						if((*t)->walls[i] == Tile::EAST)
						{
							return true;
						}
					}
				}
				n++;
			}
			break;
		case SOUTH:
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == tile)
				{
					if(tile == standingPos)
					for(int i = 0; i != 4; i++)
					{

						if((*t)->walls[i] == Tile::SOUTH)
						{
							return true;
						}
					}
					if(tile != standingPos)
					{

						for(int i = 0; i != 4; i++)
						{
							if((*t)->walls[i] == Tile::NORTH)
							{
								return true;
							}

						}
						(*t)->addBeam(2);
					}
					if(tile != standingPos)
						if((*t)->occupied != nullptr && (*t)->occupied != this)
						{
							(*t)->occupied->takeDamage();
							return true;
						}
					for(int i = 0; i != 4; i++)
					{

						if((*t)->walls[i] == Tile::SOUTH)
						{
							return true;
						}
					}
				}
				n++;
			}
			break;
		case WEST:
			for(auto t = map->tile.begin(); t != map->tile.end(); t++)
			{
				if(n == tile)
				{
					if(tile == standingPos)
					for(int i = 0; i != 4; i++)
					{

						if((*t)->walls[i] == Tile::WEST)
						{
							return true;
						}
					}
					if(tile != standingPos)
					{

						for(int i = 0; i != 4; i++)
						{
							if((*t)->walls[i] == Tile::EAST)
							{
								return true;
							}

						}
						(*t)->addBeam(3);
					}
					if(tile != standingPos)
						if((*t)->occupied != nullptr && (*t)->occupied != this)
						{
							(*t)->occupied->takeDamage();
							return true;
						}
					for(int i = 0; i != 4; i++)
					{

						if((*t)->walls[i] == Tile::WEST)
						{
							return true;
						}
					}

				}
				n++;
			}

			break;
		}
		//test map end
		if(h < 0 || h > map->map_h )
		{
			return true;
		}
		if((w == 0 && dir == -1) || (estW == 0 && dir == 1))
		{
			return true;
		}
		tile += dir;
	}

}
