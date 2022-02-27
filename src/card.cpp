#include "card.h"

Card::Card(Type type, int variant, int power)
{
	this->type = type;
	this->variant = variant;
	this->power = power;
	state = IN_DECK;
	inHand = 0;
	hidden = true;
}

Card::Card()
{
	state = IN_DECK;
	inHand = 0;
	hidden = true;
}

void Card::draw()
{
	if(!hidden)
		switch (type) {
		case MOVE:
			for (int i = 0 ; i< 4 ; i++)
				if(variant == i)
				{
					tex->texMove->place(x,y);
					tex->texMove->draw(i);
				}
			break;
		case ROTATE:
			for (int i = 0 ; i< 3 ; i++)
				if(variant == i)
				{
					tex->texRotate->place(x,y);
					tex->texRotate->draw(i);
				}
			break;
		default:
			tex->texHidden->place(x,y);
			tex->texHidden->draw(0);
			break;
		}
	else
	{

		tex->texHidden->place(x,y);
		tex->texHidden->draw(0);
	}
}
void Card::addTexture(Texture *tex)
{
	this->tex = tex;
}

void Card::place(int x, int y)
{
	this->x = x;
	this->y = y;
}
