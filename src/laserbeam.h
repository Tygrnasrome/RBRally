#ifndef LASERBEAM_H
#define LASERBEAM_H

#include "tile.h"

#define BEAM_W 4
class LaserBeam
{
public:
	LaserBeam(int x, int y ,int dir);
	void place(int x, int y);
	void changeDir(int dir);
	void draw();

	int x,y,dir;
};

#endif // LASERBEAM_H
