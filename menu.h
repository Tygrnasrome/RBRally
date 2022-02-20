#ifndef MENU_H
#define MENU_H

#include <vector>
#include "screen.h"
#include "grafika.h"
#include "button.h"

class Menu : public Screen
{
public:
	Menu();
	std::vector<Button*> buttons;

	virtual void add(Button* b);

	virtual void draw();
	virtual void update();
	virtual void event(SDL_Event* e);
	virtual void keystate(Uint8* kst);
	Obrazek *title;
};

#endif // MENU_H
