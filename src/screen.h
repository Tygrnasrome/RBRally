#ifndef SCREEN_H
#define SCREEN_H

#include <SDL/SDL.h>

class Screen
{
public:
	Screen();

	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void event(SDL_Event* e) = 0;
	virtual void keystate(Uint8* kst) = 0;

};

#endif // SCREEN_H
