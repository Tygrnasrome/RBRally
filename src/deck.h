#ifndef DECK_H
#define DECK_H
#include "card.h"
#include "texture.h"

#include <list>
#include <array>

class Deck
{
public:
	Deck();
	int size, moveOneC, moveTwoC, moveThreeC, backUpC, rotateLC, rotateRC, uturnC, dpx, dpy, dy, dx;
	void addDeck(Deck *deck);
	void placeDeck(int x, int y);
	void placeDiscardPile(int x, int y);
	void placeRegister(int x, int y, int num);
	void placeHand(int x, int y, Player *player);
	void draw(Player *player);
	void placeCards();
	void drawCards(Player* player, int owned);
	void discard(Player* player);
	void createDeck();
	void shuffle();
	void copyCard(Card *copy, Card* original);
	Obrazovka* obrazovka = Obrazovka::instance();
	std::list<Card*> cards;
	Texture *tex;

};

#endif // DECK_H
