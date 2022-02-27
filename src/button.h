#ifndef BUTTON_H
#define BUTTON_H

#include <functional>
//#include <SDL_mixer.h>

#include "grafika.h"

class Button
{
public:
	Button(const char*fn, std::function<void()> klik);
	Button();
	std::function<void()> klik;
	virtual void execute_klik(int x, int y);
	Obrazek obr;
	virtual void draw(int x, int y);
	bool ramecek;
//	Mix_Chunk *button_click;
};

#endif // BUTTON_H
