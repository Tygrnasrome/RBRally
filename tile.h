#ifndef TILE_H
#define TILE_H

#include "grafika.h"
#include "texture.h"

#define TILE_SIZE 50
#define WALL_SIZE 5

class Tile
{
public:
	Tile();

	void draw(int x, int y);
	void border(int x, int y);
	void empty(int x, int y);
	void belt(int x, int y);
	void fast_belt(int x, int y);
	void left_rotator(int x, int y);
	void right_rotator(int x, int y);
	void hole(int x, int y);
	void repair(int x, int y, int type);

	void wall(int x, int y);
	void laser(int x, int y);

	void setType(int num);
	void setFacing(int num);
	void addWall(int num, int facing);
	void addLaser(int num, int facing);
	void addTexture(Texture *tex);
	int getWall(int id);
	int getLaser(int id);
	typedef enum{
		EMPTY,
		STR_BELT,
		LEFT_BELT,
		RIGHT_BELT,
		UNI_BELT,
		T_BELT,
		STR_FAST_BELT,
		LEFT_FAST_BELT,
		RIGHT_FAST_BELT,
		UNI_FAST_BELT,
		T_FAST_BELT,
		RIGHT_ROTATOR,
		LEFT_ROTATOR,
		HOLE,
		REPAIR,
		MODIFY
	}Type;

	typedef enum{
		NONE,
		NORTH,
		EAST,
		SOUTH,
		WEST

	}Facing;


	Texture *tex;
	Type type;
	Facing facing;
	Facing walls[4];
	Facing lasers[4];

	int tile_size;
};

#endif // TILE_H
