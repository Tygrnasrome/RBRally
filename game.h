#ifndef GAME_H
#define GAME_H
#include "map.h"
#include "screen.h"

class Game : public Screen
{
public:
	Game();
	virtual void draw();
	virtual void update();
	virtual void event(SDL_Event* e);
	virtual void keystate(Uint8* kst);

	Map* map, *startMap;

};

#endif // GAME_H
