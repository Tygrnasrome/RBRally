#include "game.h"

Game::Game()
{
	map = new Map();
	map_one = new Map("maps/map0.txt");
	startMap = new Map("maps/start.txt");
	map->addMap(map_one);
	map->addMap(startMap);
	map->setSize(12,16);
	map->draw();
	startMap->draw();

	deck = new Deck();
	deck->placeDeck(map->x + map->map_w*TILE_SIZE + 10, map->y);
	deck->placeDiscardPile(map->x + map->map_w*TILE_SIZE + 10, map->y + 200);

	for(int i = 1 ; i < playerNum ; i++)
	{
		int num = 0;
		for(auto it = map->tile.begin(); it != map->tile.end(); it++)
		{
			if(num == map->startingPos[i])
				player.push_back(new Player((*it)->x,(*it)->y,num));
			num++;
		}
	}
	int i = 0;
	for(auto it = player.begin(); it != player.end(); it++)
	{
		Player *t[playerNum];
		t[i] =  *it;
		activePlayer =  t[7];
		i++;
	}

}
void Game::draw()
{
	map->draw();
	startMap->draw();

	for(auto it = player.begin(); it != player.end(); it++)
	{
		if(!(*it)->dead)
			(*it)->draw();
	}
	deck->draw(activePlayer);
}
void Game::update()
{

	for(auto p = player.begin(); p != player.end(); p++)
	{
		int num = 0;
		for(auto t = map->tile.begin(); t != map->tile.end(); t++)
		{
			if(num == (*p)->standingPos)
			{
				if(!(*p)->dead)
					(*t)->occupied = *p;

				(*p)->update((*t)->x + TILE_SIZE/2,(*t)->y + TILE_SIZE/2);
				for(auto til = map->tile.begin(); til != map->tile.end(); til++)
				{
					if((*til)->occupied == *p && (*til) != (*t) || (*til)->occupied == *p && (*p)->dead)
						(*til)->occupied = 0;
				}
			}
			num++;
		}

	}
	deck->placeDeck(map->x + map->map_w*TILE_SIZE + 10, map->y);
	deck->placeDiscardPile(map->x + map->map_w*TILE_SIZE + 10, map->y + 200);

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

			activePlayer->facing = Player::WEST;

			break;
		case SDLK_UP:

			activePlayer->facing = Player::NORTH;

			break;
		case SDLK_RIGHT:

			activePlayer->facing = Player::EAST;

			break;
		case SDLK_DOWN:

			activePlayer->facing = Player::SOUTH;

			break;
		case SDLK_r:

			for(auto it = player.begin(); it != player.end(); it++)
			{
				if((*it)->dead)
					(*it)->revive();
			}

			break;
		case SDLK_b:
			printf("\n----------------	 BOARD MOVEMENT		---------------------------\n\n");
			for(auto it = player.begin(); it != player.end(); it++)
			{

				map->boardMovement(*it);
			}

			break;

		case SDLK_l:
			printf("\n----------------	 LASER SHOOT		---------------------------\n\n");
				map->laserShoot();
				for(auto it = player.begin(); it != player.end(); it++)
				{
					if(!(*it)->dead)
						(*it)->testDamage();
				}
			break;
		case SDLK_c:
			printf("\n----------------	 CARD DRAWING	---------------------------\n\n");

//				for(auto it = player.begin(); it != player.end(); it++)
//				{
//					if(!(*it)->dead)
//						deck->drawCards(*it);
//				}
			deck->drawCards(activePlayer);
			break;

		case SDLK_v:

			for(auto it = player.begin(); it != player.end(); it++)
			{
				if(!(*it)->dead)
					(*it)->shoot(map);
			}
			for(auto it = player.begin(); it != player.end(); it++)
			{
				if(!(*it)->dead)
					(*it)->testDamage();
			}
			break;
		case SDLK_w:

			activePlayer->move(1,map);

			break;
		}

	}
}
void Game::keystate(Uint8* kst)
{

}
