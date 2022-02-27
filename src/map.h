#ifndef MAP_H
#define MAP_H
#include "grafika.h"
#include "texture.h"
#include "tile.h"
#include "player.h"

#include <array>
#include <list>


#define MAP_SIZE 12
class Player;
class Tile;
class Map
{
public:

	Map();
	Map(const char*fn);
	void draw();
	void load(const char*fn);
	void place(int x, int y);
	void setWall(int id, int type, int num);
	void setLaser(int id, int type, int num);
	void addMap(Map* map);
	void delMap();
	void setSize(int map_w, int map_h);
	void boardMovement(Player *player);
	void rotatorMovement(Player *player);
	void beltMovement(int beltType,Player *player);
	bool laserShoot();
	void clearBeams();
	int map_w, map_h, map_size, x, y, initX, initY, addedSize;
	int startingPos[12];
	std::list<Map*> map;
	std::array<Tile*,MAP_SIZE*MAP_SIZE> tiles;
	std::list<Tile*> tile;
	Texture *texture;



};

#endif // MAP_H
