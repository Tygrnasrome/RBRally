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
	void drawSelectingRect();
	void createFile(const char *fn);
	void loadFile(const char *fn);
	void addObject();
	void changeSize(int x, int y);
	Map* map;
	int rotation = 1;
	int type = 1;
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
		LASER

	}Type;
	int walls[4];
	Type building_state;
	int selectedTileX = 1;
	int selectedTileY = 1;
	int map_w = 12;
	int map_h = 12;
};

#endif // MAPBUILDER_H
