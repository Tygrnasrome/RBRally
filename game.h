#ifndef GAME_H
#define GAME_H
#include "map.h"
#include "screen.h"
#include "player.h"

class Game : public Screen
{
public:
	Game();
	virtual void draw();
	virtual void update();
	virtual void event(SDL_Event* e);
	virtual void keystate(Uint8* kst);

	int playerNum = 9;
	Map* map, *startMap, *map_one;
	std::list<Player*> player;
	Player* activePlayer;
	Obrazovka* obrazovka = Obrazovka::instance();

};

#endif // GAME_H
