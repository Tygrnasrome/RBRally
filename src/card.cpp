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

void Card::addTexture(TexturePack *tex)
{
	this->tex = tex;
}

void Card::place(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Card::executeKlik(int x, int y, int buttonType)
{
	if (x > this->x && x < (this->x +tex->texMove->w) && y > this->y && y < (this->y +tex->texMove->h))
	{
		if(!buttonType)
			enlarge();
		if(buttonType)
			klik();
	}
}

void Card::enlarge()
{
	hidden = true;
}

void Card::klik()
{
	if(inHand != nullptr && state == IN_REGISTER)
		for(int i = 0 ; i<5 ; i++)
		{
			if(inHand->registers[i]->full == this)
			{
				state = IN_HAND;
				inHand->registers[i]->full = nullptr;
				i= 5;
			}
		}else

		if(inHand != nullptr && state == IN_HAND)
			for(int i = 0 ; i<5 ; i++)
			{
				if(inHand->registers[i]->full == nullptr)
				{
					state = IN_REGISTER;
					x = inHand->registers[i]->x;
					y = inHand->registers[i]->y;
					inHand->registers[i]->full = this;
					i= 5;
				}
			}


}
