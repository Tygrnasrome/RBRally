#ifndef REGISTER_H
#define REGISTER_H
#include "player.h"
#include "card.h"

class Card;
class Player;
class Register
{
public:
	Register();
	int x, y;
	bool locked;
	void place(int x,int y);
	Player* belong;
	Card* full;
};

#endif // REGISTER_H
