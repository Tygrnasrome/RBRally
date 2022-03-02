#include "deck.h"

Deck::Deck()
{
	tex = new TexturePack();
	moveOneC = moveTwoC = moveThreeC = backUpC = rotateLC = rotateRC =uturnC = 3;
	size = moveOneC + moveTwoC + moveThreeC + backUpC + rotateLC + rotateRC + uturnC;

	createDeck();
}

void Deck::createDeck()
{
	int rand, tmpOne, tmpTwo, tmpThree, tmpBack, tmpLeft, tmpRight, tmpU, tempSize;
	tmpOne = tmpTwo = tmpThree = tmpBack = tmpLeft = tmpRight = tmpU = tempSize = 0;
	while(tempSize != size)
	{
		rand = nahoda(6);
		switch (rand) {
		case 0:
			if (tmpOne < moveOneC)
			{
				cards.push_back(new Card(Card::MOVE, 1, 100));
				tmpOne++;
				tempSize++;
			}
			break;
		case 1:
			if (tmpTwo < moveTwoC)
			{
				cards.push_back(new Card(Card::MOVE, 2, 200));
				tmpTwo++;
				tempSize++;
			}
			break;
		case 2:
			if (tmpThree < moveThreeC)
			{
				cards.push_back(new Card(Card::MOVE, 3, 300));
				tmpThree++;
				tempSize++;
			}
			break;
		case 3:
			if (tmpBack < backUpC)
			{
				cards.push_back(new Card(Card::MOVE, 0, 50));
				tmpBack++;
				tempSize++;
			}
			break;
		case 4:
			if (tmpLeft < rotateLC)
			{
				cards.push_back(new Card(Card::ROTATE, 0, 80));
				tmpLeft++;
				tempSize++;
			}
			break;
		case 5:
			if (tmpRight < rotateRC)
			{
				cards.push_back(new Card(Card::ROTATE, 1, 85));
				tmpRight++;
				tempSize++;
			}
			break;
		case 6:
			if (tmpU < uturnC)
			{
				cards.push_back(new Card(Card::ROTATE, 2, 90));
				tmpU++;
				tempSize++;
			}
			break;


		default:
			printf("rand missed case: %d\n", rand);
			break;
		}
	}
	//	for(int i = 0 ; i < moveOneC ; i++)
	//	{
	//		cards.push_back(new Card(Card::MOVE, 1, 100));
	//	}
	//	for(int i = 0 ; i < moveTwoC ; i++)
	//	{
	//		cards.push_back(new Card(Card::MOVE, 2, 200));
	//	}
	//	for(int i = 0 ; i < moveThreeC ; i++)
	//	{
	//		cards.push_back(new Card(Card::MOVE, 3, 300));
	//	}
	//	for(int i = 0 ; i < backUpC ; i++)
	//	{
	//		cards.push_back(new Card(Card::MOVE, -1, 50));
	//	}
	//	for(int i = 0 ; i < rotateLC ; i++)
	//	{
	//		cards.push_back(new Card(Card::ROTATE, -1, 80));
	//	}
	//	for(int i = 0 ; i < rotateRC ; i++)
	//	{
	//		cards.push_back(new Card(Card::ROTATE, 1, 85));
	//	}
	//	for(int i = 0 ; i < uturnC ; i++)
	//	{
	//		cards.push_back(new Card(Card::ROTATE, 2, 90));
	//	}
	for(auto it = cards.begin(); it != cards.end(); it++)
	{
		(*it)->addTexture(tex);
	}
	shuffle();
}

void Deck::executeKlik(int x, int y, int buttonType)
{
	for(auto it = cards.begin(); it != cards.end(); it++)
	{
		(*it)->executeKlik(x, y, buttonType);
	}
}

void Deck::shuffle()
{
	int rand, number, inDeckSize, tmpSize;
	inDeckSize = tmpSize = 0;
	bool taken[size];
	for (int i = 0 ; i<size ; i++)
		taken[i] = 0;
	number = 0;
	//shuffle only inDeck and inDiscardPile cards
	for(auto it = cards.begin(); it != cards.end(); it++)
	{


		if((*it)->state == Card::IN_DISCARD_PILE)
		{
			(*it)->state = Card::IN_DECK;
		}
		if((*it)->state == Card::IN_DECK)
			inDeckSize++;
		if((*it)->state != Card::IN_DECK)
			taken[number] = true;
		number++;
	}
	Card*tmpCards[inDeckSize];

	//creating paralel deck with random order
	while(tmpSize != inDeckSize)
	{
		number = 0;
		rand = nahoda(size);
		if(!taken[rand])
			for(auto it = cards.begin(); it != cards.end(); it++)
			{
				if(number == rand)
				{
					taken[rand] = true;
					tmpCards[tmpSize] = new Card();
					copyCard(tmpCards[tmpSize], *it);
					tmpSize++;
				}
				number++;
			}
	}

	//clear old inDeck cards
	for(auto it = cards.begin(); it != cards.end(); it++)
	{
		if((*it)->state == Card::IN_DECK)
		{
			delete *it;
			it = cards.erase(it);
			it--;
		}
	}

	//add pararel deck to the real one
	for(auto it = 0; it != inDeckSize; it++)
	{
		cards.push_front(tmpCards[it]);
	}

	//set new inDeck cards to hidden
	for(auto it = cards.begin(); it != cards.end(); it++)
	{
		if((*it)->state == Card::IN_DECK)
		{
			(*it)->hidden = true;
		}
	}

}

void Deck::copyCard(Card *copy, Card *original)
{
	copy->hidden = original->hidden;
	copy->inHand = original->inHand;
	copy->power = original->power;
	copy->x = original->x;
	copy->y = original->y;
	copy->state = original->state;
	copy->type = original->type;
	copy->variant = original->variant;
	copy->tex = original->tex;
}
void Deck::draw(Player* player)
{
	int number = 0;
	//	draw (paint) cards
	placeCards();
	int i = 0;
	//count how many cards to draw
	for(auto it = cards.begin(); it != cards.end(); it++)
	{

		if((*it)->inHand == player && (*it)->state == Card::IN_HAND)
		{
			number++;
		}
	}
	for(auto it = cards.begin(); it != cards.end(); it++)
	{

		if((*it)->inHand == player && (*it)->state == Card::IN_HAND)
		{
			(*it)->x = obrazovka->w/5 - (number*30) + (i*60);
			(*it)->y = obrazovka->h/2 - 250;
			(*it)->hidden = false;
			i++;
		}

		(*it)->draw();

	}
}

void Deck::placeCards()
{
	//place
	for(auto it = cards.begin(); it != cards.end(); it++)
		switch ((*it)->state) {
		case Card::IN_DECK:
			(*it)->place(dx,dy);
			break;
		case Card::IN_DISCARD_PILE:
			(*it)->place(dpx,dpy);
			break;
		case Card::IN_HAND:
			(*it)->place(dx,dy+50);
			break;
		case Card::IN_REGISTER:
			break;
		default:
			break;
		}
}


void Deck::drawCards(Player* player, int owned)
{
	int draws = player->damageMax - player->damage;
	int count = owned;
	//player draws cards
	for(auto it = cards.begin(); it != cards.end(); it++)
	{
		if ((*it)->state == Card::IN_DECK && (*it)->inHand == 0 && count < draws)
		{
			count++;
			(*it)->inHand = player;
			(*it)->state = Card::IN_HAND;
		}
	}
	if(count < draws)
	{
		//if cards are gone shuffle and draw again
		printf("the deck was out of cards and has been shuffled");
		shuffle();
		drawCards(player, count);
	}
}

void Deck::discard(Player* player, int type)
{
	//player discards cards
	for(auto it = cards.begin(); it != cards.end(); it++)
	{
		if(type == 0)
			if ((*it)->inHand == player && (*it)->state == Card::IN_HAND)
			{
				(*it)->inHand = 0;
				(*it)->state = Card::IN_DISCARD_PILE;
			}
		if(type == 1)
			if ((*it)->inHand == player)
			{
				if((*it)->state == Card::IN_REGISTER)
					for(int i = 0 ; i < 5 ; i++)
						if(player->registers[i]->full == *it && player->registers[i]->full)
							player->registers[i]->full = nullptr;
				(*it)->inHand = 0;
				(*it)->state = Card::IN_DISCARD_PILE;
			}
	}
}

void Deck::placeDeck(int x, int y)
{
	dx = x;
	dy = y;
}
void Deck::placeDiscardPile(int x, int y)
{
	dpx = x;
	dpy = y;
}
void Deck::placeRegister(int x, int y, int num)
{
	switch (num) {
	case 0:
		reg1x = x;
		reg1y = y;
		break;
	case 1:
		reg2x = x;
		reg2y = y;
		break;
	case 2:
		reg3x = x;
		reg3y = y;
		break;
	case 3:
		reg4x = x;
		reg4y = y;
		break;
	case 4:
		reg5x = x;
		reg5y = y;
		break;
	default:
		printf("warning: wrong register number: %d\n", num);
		break;
	}
}
