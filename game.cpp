#include "game.h"

Game::Game()
{
	map = new Map();
	map_one = new Map("maps/map0.txt");
	startMap = new Map("maps/start.txt");
	map->addMap(map_one);
	map->addMap(startMap);
	for(int i = 1 ; i < 9 ; i++)
		player.push_back(new Player(startMap->tiles[startMap->startingPos[i]]->x,startMap->tiles[startMap->startingPos[i]]->y,startMap->startingPos[i]));

}

void Game::draw()
{
	map->draw();
	startMap->draw();
	for(auto it = player.begin(); it != player.end(); it++)
	{
		(*it)->draw();
	}
}
void Game::update()
{
	for(auto it = player.begin(); it != player.end(); it++)
	{
		(*it)->update(startMap->tiles[(*it)->standingPos]->x + TILE_SIZE/2,startMap->tiles[(*it)->standingPos]->y + TILE_SIZE/2);
	}
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
			for(auto it = player.begin(); it != player.end(); it++)
			{
				(*it)->facing = Player::WEST;
			}
			break;
		case SDLK_UP:
			for(auto it = player.begin(); it != player.end(); it++)
			{
				(*it)->facing = Player::NORTH;
			}
			break;
		case SDLK_RIGHT:
			for(auto it = player.begin(); it != player.end(); it++)
			{
				(*it)->facing = Player::EAST;
			}
			break;
		case SDLK_DOWN:
			for(auto it = player.begin(); it != player.end(); it++)
			{
				(*it)->facing = Player::SOUTH;
			}
			break;
		}
	}
}
void Game::keystate(Uint8* kst)
{

}
