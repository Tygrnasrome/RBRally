#include "game.h"

Game::Game()
{

	map = new Map("maps/map0.txt");
	startMap = new Map("maps/start.txt");
	map->place(0,-2*TILE_SIZE);
	startMap->place(0,6*TILE_SIZE);
}

void Game::draw()
{
	map->draw();
	startMap->draw();
}
void Game::update()
{

}
void Game::event(SDL_Event* e)
{
	switch(e->type)
	{
	case SDL_KEYDOWN:
		switch(e->key.keysym.sym)
		{
		/* změna building_state */
		case SDLK_LEFT:
			map->load("maps/map0.txt");
			break;
		}
	}
}
void Game::keystate(Uint8* kst)
{

}
