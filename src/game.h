#ifndef GAME_H
#define GAME_H
#include "map.h"
#include "screen.h"
#include "player.h"
#include "deck.h"

class Map;
class Player;
class Game : public Screen
{
public:
	Game();
	virtual void draw();
	virtual void update();
	virtual void event(SDL_Event* e);
	virtual void keystate(Uint8* kst);
	void announcePhase();

	int playerNum = 9;
	typedef enum{
		DRAWING,
		PROGRAMMING,
		DISCARDING,
		REGISTER_MOVE,
		BOARD_MOVEMENT,
		SHOOT,
		REPAIR_AND_MODIFY,
		FLAG,
		REVIVE,
		SET_DIR,
		SHUTDOWN
	}Event;
	Event phase;
	Map* map, *startMap, *map_one;
	std::list<Player*> player;
	Deck *deck;
	Player* activePlayer;
	Pismo *announcement;
	Obrazovka* obrazovka = Obrazovka::instance();

};

#endif // GAME_H
