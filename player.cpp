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

void Player::move(int move, Map *map)
{


	interrupted = false;
	testMapEnd(move,map);
	testWallCollision(move,map);
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

void Player::testWallCollision(int move, Map *map)
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
							interrupted = true;
					}
				if(n == standingPos-map->map_w)
					for(int i = 0; i != 4; i++)
					{
						if((*t)->walls[i] == Tile::SOUTH)
							interrupted = true;
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
							interrupted = true;
					}
				if(n == standingPos+map->map_w)
					for(int i = 0; i != 4; i++)
					{
						if((*t)->walls[i] == Tile::NORTH)
							interrupted = true;
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
							interrupted = true;
					}
				if(n == standingPos+map->map_w)
					for(int i = 0; i != 4; i++)
					{
						if((*t)->walls[i] == Tile::NORTH)
							interrupted = true;
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
							interrupted = true;
					}
				if(n == standingPos+map->map_w)
					for(int i = 0; i != 4; i++)
					{
						if((*t)->walls[i] == Tile::SOUTH)
							interrupted = true;
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
							interrupted = true;
					}
				if(n == standingPos+1)
					for(int i = 0; i != 4; i++)
					{
						if((*t)->walls[i] == Tile::WEST)
							interrupted = true;
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
							interrupted = true;
					}
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
							interrupted = true;
					}
				if(n == standingPos-1)
					for(int i = 0; i != 4; i++)
					{
						if((*t)->walls[i] == Tile::EAST)
							interrupted = true;
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
							interrupted = true;
					}
				if(n == standingPos+map->map_w)
					for(int i = 0; i != 4; i++)
					{
						if((*t)->walls[i] == Tile::SOUTH)
							interrupted = true;
					}
				n++;
			}
		break;
	default:
		printf("neplatný enum player facing při wall collision testing");
		break;
	}

}

void Player::testMapEnd(int move, Map *map)
{
	int h = standingPos/12;
	switch (facing)
	{
	case NORTH:
		if(h == 0 && move == 1 || h == map->map_h-1 && move == -1)
		{
			dead = true;
			interrupted = true;
			break;
		}
		break;
	case SOUTH:

		if(h == map->map_h-1 && move == 1 || h == 0 && move == -1)
		{
			dead = true;
			interrupted = true;
			break;
		}
		break;
	case EAST:
		if(standingPos%12 == 11 && move == 1 || standingPos%12 == 0 && move == -1)
		{
			dead = true;
			interrupted = true;
			break;
		}
		break;
	case WEST:
		if(standingPos%12 == 0 && move == 1 || standingPos%12 == 11 && move == -1)
		{
			dead = true;
			interrupted = true;
			break;
		}
		break;
	default:
		break;
	}
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
	testMapEnd(mov,map);
	testWallCollision(mov,map);
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
