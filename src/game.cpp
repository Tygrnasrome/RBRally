#include "game.h"

Game::Game()
{
	announcement = new Pismo();
	announcement->nacti("textures/fonts/announcement.png","abcdefghijklmnopqrstuvwxyz!?.,0123 456789");
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
	phase = DRAWING;

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
	/*	typing annoucement	*/
	announcePhase();
}

void Game::announcePhase()
{
	switch (phase)
	{
	case DRAWING:
		announcement->umisti(obrazovka->w/2 - 230, 20);
		announcement->kresli("drawing cards");
		break;

	case PROGRAMMING:
		announcement->umisti(obrazovka->w/2 - 340, 20);
		announcement->kresli("programming registers");
		break;

	case DISCARDING:
		announcement->umisti(obrazovka->w/2 - 260, 20);
		announcement->kresli("discarding cards");
		break;

	case REGISTER_MOVE:
		announcement->umisti(obrazovka->w/2 - 230, 20);
		announcement->kresli("robot   moves");
		announcement->umisti(obrazovka->w/2 - 35, 20);
		int playerID;
		playerID = 0;
		for(auto it = player.begin(); it != player.end(); it++)
		{
			if(*it == activePlayer)
				announcement->kresli(playerID+1);
			playerID++;
		}

		break;

	case BOARD_MOVEMENT:
		announcement->umisti(obrazovka->w/2 - 200, 20);
		announcement->kresli("board moves");
		break;

	case SHOOT:
		announcement->umisti(obrazovka->w/2 - 370, 20);
		announcement->kresli("players and lasers shoot");
		break;

	case REPAIR_AND_MODIFY:
		announcement->umisti(obrazovka->w/2 - 270, 20);
		announcement->kresli("repair and modify");
		break;

	case FLAG:
		announcement->umisti(obrazovka->w/2 - 215, 20);
		announcement->kresli("capturing flag");
		break;

	case REVIVE:
		announcement->umisti(obrazovka->w/2 - 360, 20);
		announcement->kresli("reviving destroyed players");
		break;

	case SET_DIR:
		announcement->umisti(obrazovka->w/2 - 205, 20);
		announcement->kresli("set direction");
		break;

	case SHUTDOWN:
		announcement->umisti(obrazovka->w/2 - 340, 20);
		announcement->kresli("commencing shutdown");
		break;
	}
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
					if(((*til)->occupied == *p && (*til) != (*t)) || ((*til)->occupied == *p && (*p)->dead))
						(*til)->occupied = nullptr;
				}
			}
			num++;
		}

	}
	deck->placeDeck(map->x + map->map_w*TILE_SIZE + 10, map->y);
	deck->placeDiscardPile(map->x + map->map_w*TILE_SIZE + 10, map->y + 200);
	for (int i = 0 ; i<5 ; i++)
	{
		int x = obrazovka->w/2 - 5*90 + i*180;
		int y = obrazovka->h - 250;
		activePlayer->registers[i]->place(x,y);
	}
	if(phase != SHOOT)
		map->clearBeams();
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
			phase = REGISTER_MOVE;
			activePlayer->facing = Player::WEST;

			break;
		case SDLK_UP:
			phase = REGISTER_MOVE;
			activePlayer->facing = Player::NORTH;

			break;
		case SDLK_RIGHT:
			phase = REGISTER_MOVE;
			activePlayer->facing = Player::EAST;

			break;
		case SDLK_DOWN:
			phase = REGISTER_MOVE;
			activePlayer->facing = Player::SOUTH;

			break;
		case SDLK_r:
			phase = REVIVE;
			for(auto it = player.begin(); it != player.end(); it++)
			{
				if((*it)->dead)
					(*it)->revive();
			}

			break;
		case SDLK_b:
			printf("\n----------------	 BOARD MOVEMENT		---------------------------\n\n");
			phase = BOARD_MOVEMENT;
			for(auto it = player.begin(); it != player.end(); it++)
			{

				map->boardMovement(*it);
			}

			break;

		case SDLK_l:
			printf("\n----------------	 LASER AND PLAYER SHOOT		---------------------------\n\n");
			phase = SHOOT;
			map->laserShoot();
			for(auto it = player.begin(); it != player.end(); it++)
			{
				if(!(*it)->dead)
					(*it)->testDamage();
			}
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
		case SDLK_c:
			printf("\n----------------	 CARD DRAWING	---------------------------\n\n");

			//				for(auto it = player.begin(); it != player.end(); it++)
			//				{
			//					if(!(*it)->dead)
			//						deck->drawCards(*it);
			//				}
			deck->discard(activePlayer);
			deck->drawCards(activePlayer, 0);
			phase = DRAWING;
			break;
		case SDLK_w:
			phase = REGISTER_MOVE;
			activePlayer->move(1,map);

			break;
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
	{
		switch (phase)
		{
		case DRAWING:
			phase = PROGRAMMING;
			break;

		case PROGRAMMING:
			phase = DISCARDING;
			break;

		case DISCARDING:
			phase = REGISTER_MOVE;
			break;

		case REGISTER_MOVE:
			phase = BOARD_MOVEMENT;
			break;

		case BOARD_MOVEMENT:
			phase = SHOOT;
			break;

		case SHOOT:
			phase = REPAIR_AND_MODIFY;
			break;

		case REPAIR_AND_MODIFY:
			phase = FLAG;
			break;

		case FLAG:
			phase = REVIVE;
			break;

		case REVIVE:
			phase = SET_DIR;
			break;

		case SET_DIR:
			phase = SHUTDOWN;
			break;

		case SHUTDOWN:
			phase = DRAWING;
			break;
		}
		break;
	}

	}
}
void Game::keystate(Uint8* kst)
{

}
