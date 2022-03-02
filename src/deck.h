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
	int reg1x, reg1y, reg2x, reg2y, reg3x, reg3y, reg4x, reg4y, reg5x, reg5y;
	void addDeck(Deck *deck);
	void placeDeck(int x, int y);
	void placeDiscardPile(int x, int y);
	void placeRegister(int x, int y, int num);
	void placeHand(int x, int y, Player *player);
	void draw(Player *player);
	void placeCards();
	void drawCards(Player* player, int owned);
	void discard(Player* player, int type);
	void createDeck();
	void shuffle();
	void copyCard(Card *copy, Card* original);
	void executeKlik(int x, int y, int buttonType);
	Obrazovka* obrazovka = Obrazovka::instance();
	std::list<Card*> cards;
	TexturePack *tex;

};

#endif // DECK_H
