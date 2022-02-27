#include <SDL/SDL.h>

#include "grafika.h"

#include "screen.h"
#include "game.h"
#include "menu.h"
#include "mapbuilder.h"


Screen* screen;
Menu* main_menu;
Game* game;
MapBuilder* mapBuilder;

float mouseX = 0;
float mouseY = 0;

void assign_buttons()
{
	main_menu->add(new Button("textures/menu_buttons/Start.png", [&] ()
	{
		screen = game;
	}));
	main_menu->add(new Button("textures/menu_buttons/levelMaker.png", [] ()
	{
		screen = mapBuilder;
	}));
	main_menu->add(new Button("textures/menu_buttons/Quit.png", [] ()
	{
		SDL_Quit();
		exit (0);
	}));
}

int main(int argc, char** argv)
{
	Obrazovka* obrazovka = Obrazovka::instance();
	obrazovka->inicializuj(1600, 1200, 0, SDL_RESIZABLE);
	Uint8* keystate = SDL_GetKeyState(NULL);

	game = new Game();
	mapBuilder = new MapBuilder();
	main_menu = new Menu();


	screen = main_menu;

	assign_buttons();



	while(1)
	{
		obrazovka->smaz();
		/* zacatek kresleni */
		screen->draw();
		screen->update();
		screen->keystate(keystate);

		/* konec kresleni */
		obrazovka->aktualizuj();
		
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			screen->event(&event);
			switch(event.type)
			{
			case SDL_VIDEORESIZE:
				SDL_FreeSurface(obrazovka->screen);
			{
				if(event.resize.w<=800)
					event.resize.w = 800;
				if(event.resize.h<=800)
					event.resize.h = 800;
				obrazovka->screen = SDL_SetVideoMode( event.resize.w,  event.resize.h,0,SDL_RESIZABLE);
				obrazovka->w = event.resize.w;
				obrazovka->h = event.resize.h;
				screen->draw();
				break;
			}
			case SDL_MOUSEMOTION:
				mouseX = event.motion.x;
				mouseY = event.motion.y;
				break;

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					if(screen == main_menu)
					{

						SDL_Quit();
						return (0);
					}
					screen = main_menu;
					break;
				}
				break;
			}
		}
	}
}

