#include "laserbeam.h"

LaserBeam::LaserBeam(int x, int y, int dir)
{
	this->x = x;
	this->y = y;
	this->dir = dir;
}

void LaserBeam::place(int x, int y)
{
	this->x = x;
	this->y = y;
}

void LaserBeam::changeDir(int dir)
{
	this->dir = dir;
}

void LaserBeam::draw()
{
	int x1, x2, y1, y2;
	barva(CERVENA);
	if (dir == 0 || dir == 2)
	{
		x1 = x + TILE_SIZE/2 - BEAM_W/2;
		y1 = y;
		x2 = x1+BEAM_W;
		y2 = y+TILE_SIZE;
	}
	if (dir == 1 || dir == 3)
	{
		x1 = x ;
		y1 = y+ TILE_SIZE/2 - BEAM_W/2;
		x2 = x+TILE_SIZE;
		y2 = y1+BEAM_W;
	}
	obdelnik(x1,y1,x2,y2);
}
