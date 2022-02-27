#ifndef MAPBUILDER_H
#define MAPBUILDER_H
#include "screen.h"
#include "map.h"


class MapBuilder : public Screen
{
public:
	MapBuilder();
	virtual void draw();
	virtual void update();
	virtual void event(SDL_Event* e);
	virtual void keystate(Uint8* kst);
	void drawSelectingRect(int id);
	void createFile(const char *fn);
	void loadFile(const char *fn);
	void addObject(Map *map);
	void changeSize(int x, int y);
	void setBuildingState();
	void erase(Map *map);
	Map* map, *draw_options, *example_tile;
	int rotation = 1;
	Obrazovka* obrazovka = Obrazovka::instance();
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
		MODIFY,
		WALL,
		LASER,
		ERASE

	}Type;
	int walls[4];
	Type building_state;
	int selectedTileX, selTypeTileX = 0;
	int selectedTileY, selTypeTileY = 0;
	int map_w = 12;
	int map_h = 12;
};

#endif // MAPBUILDER_H
