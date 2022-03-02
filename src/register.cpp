#include "register.h"

Register::Register()
{
	full = nullptr;
	locked = false;
}

void Register::place(int x, int y)
{
	this->x = x;
	this->y = y;
}
