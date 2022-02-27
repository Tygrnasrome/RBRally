#ifndef REGISTER_H
#define REGISTER_H
#include "player.h"

class Player;
class Register
{
public:
	Register();
	int x, y;
	void place(int x,int y);
	Player* belong;
};

#endif // REGISTER_H
