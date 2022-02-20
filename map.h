#ifndef MAP_H
#define MAP_H
#include "grafika.h"
#include "texture.h"
#include "tile.h"

#include <array>
#include <list>


#define MAP_SIZE 12


class Map
{
public:

	Map(const char*fn);
	void draw();
	void load(const char*fn);
	void place(int x, int y);
	void setWall(int id, int type, int num);
	void setLaser(int id, int type, int num);
	void addMap(Map* map,const char*fn);
	int map_w, map_h, map_size, x, y, initX, initY;
	int startingPos[12];
	std::list<Map*> map;
	std::array<Tile*,MAP_SIZE*MAP_SIZE> tiles;
	Texture *texture;



};

#endif // MAP_H
