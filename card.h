#ifndef CARD_H
#define CARD_H

#include "texture.h"
#include "player.h"
class Card
{
public:
	typedef enum{
		MOVE,
		ROTATE
	}Type;
	typedef enum{
		IN_DECK,
		IN_HAND,
		IN_DISCARD_PILE,
		IN_REGISTER
	}State;

	Card(Type type, int variant, int power);
	Card();
	void place(int x, int y);
	void draw();
	void addTexture(Texture *tex);
	Type type;
	State state;
	Texture *tex;
	Player* inHand;
	int variant, power, x, y;
	bool hidden = false;
	//Player* shown;
};

#endif // CARD_H
