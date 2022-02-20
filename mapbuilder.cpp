#include "mapbuilder.h"

MapBuilder::MapBuilder()
{
	map = new Map("maps/custom.txt");
	rotation = 1;
	for(int i = 0 ; i < 4 ; i ++)
	{
		walls[i] = 0;
	}
}
void MapBuilder::draw()
{
	map->draw();
	drawSelectingRect();
}

void MapBuilder::drawSelectingRect()
{
	if (selectedTileX < 0) selectedTileX = 0;
	if (selectedTileX >= map->map_w) selectedTileX = map->map_w -1;

	if (selectedTileY < 0) selectedTileY = 0;
	if (selectedTileY >= map->map_h) selectedTileY = map->map_h -1;
	barva(CERVENA);
	//červený obdélníček, kolem aktivního políčka
	obdelnik(selectedTileX*TILE_SIZE + map->x,selectedTileY*TILE_SIZE + map->y,(selectedTileX+1)*TILE_SIZE+1 + map->x,selectedTileY*TILE_SIZE+1 + map->y);
	obdelnik((selectedTileX+1)*TILE_SIZE + map->x,selectedTileY*TILE_SIZE + map->y,(selectedTileX+1)*TILE_SIZE+1 + map->x,(selectedTileY+1)*TILE_SIZE+1 + map->y);
	obdelnik(selectedTileX*TILE_SIZE + map->x,(selectedTileY+1)*TILE_SIZE + map->y,(selectedTileX+1)*TILE_SIZE+1 + map->x,(selectedTileY+1)*TILE_SIZE+1 + map->y);
	obdelnik(selectedTileX*TILE_SIZE + map->x,selectedTileY*TILE_SIZE + map->y,selectedTileX*TILE_SIZE+1 + map->x,(selectedTileY+1)*TILE_SIZE+1 + map->y);
}
void MapBuilder::update()
{

}
void MapBuilder::event(SDL_Event* e)
{
	switch(e->type)
	{
	case SDL_KEYDOWN:
		switch(e->key.keysym.sym)
		{
		/* změna building_state */
		case SDLK_1:
			building_state = EMPTY;
			break;
		case SDLK_2:
			switch (type) {

			case 1:
				building_state = STR_BELT;
				break;
			case 2:
				building_state = RIGHT_BELT;
				break;
			case 3:
				building_state = LEFT_BELT;
				break;
			case 4:
				building_state = UNI_BELT;
				break;
			}

			break;
		case SDLK_3:
			switch (type) {
			case 1:
				building_state = STR_FAST_BELT;
				break;
			case 2:
				building_state = RIGHT_FAST_BELT;
				break;
			case 3:
				building_state = LEFT_FAST_BELT;
				break;
			case 4:
				building_state = UNI_FAST_BELT;
				break;
			}
			break;
		case SDLK_4:
			building_state = RIGHT_ROTATOR;
			break;
		case SDLK_5:
			building_state = LEFT_ROTATOR;
			break;
		case SDLK_6:
			building_state = HOLE;
			break;
		case SDLK_7:
			building_state = WALL;
			break;
		case SDLK_8:
			building_state = LASER;
			break;
		case SDLK_r:
			rotation++;
			if(rotation == 5)
				rotation = 1;
			break;
		case SDLK_t:
			type++;
			if(type == 5)
				type = 1;
			break;


		case SDLK_LEFT:
		case SDLK_a:
			changeSize(-1,0);

			break;
		case SDLK_RIGHT:
		case SDLK_d:
			changeSize(1,0);

			break;
		case SDLK_UP:
		case SDLK_w:
			changeSize(0,1);

			break;
		case SDLK_DOWN:
		case SDLK_s:
			changeSize(0,-1);

			break;

			/* renderování .txt souboru */

		}
		break;
	case SDL_MOUSEMOTION:
	{
		selectedTileX = e->motion.x / TILE_SIZE - map->x/ TILE_SIZE;
		selectedTileY = e->motion.y / TILE_SIZE - map->y/ TILE_SIZE;
		drawSelectingRect();
		break;
	}
	case SDL_MOUSEBUTTONDOWN:
	{
		addObject();
		break;
	}
		//	case SDL_VIDEORESIZE:
		//		SDL_FreeSurface(obrazzovka->screen);
		//		obrazzovka->screen = SDL_SetVideoMode(e->resize.w, e->resize.h,0,SDL_RESIZABLE);
		//		break;

	}
}

void MapBuilder::changeSize(int x, int y)
{
	map_h += y;
	map_w += x;
	if (!map_h)
		map_h = 1;
	if (!map_w)
		map_w = 1;
	if(map_h > 12)
		map_h = 12;

	if(map_w > 12)
		map_w = 12;
	createFile("maps/custom.txt");
	loadFile("maps/custom.txt");
}


void MapBuilder::createFile(const char*fn)
{

	FILE* f;
	f=fopen(fn, "w");

	//	fprintf(f, "num of tiles %d \n", MAP_SIZE*MAP_SIZE);
	//	fprintf(f, "num of rows %d \n", MAP_SIZE);
	//	fprintf(f, "num of coloumms %d \n", MAP_SIZE);

	fprintf(f,"mapw %d\n", map_w);
	fprintf(f,"maph %d\n", map_h);

	for (int i = 0 ; i < (map_w*map_h) ; i++)
	{

		fprintf(f, "tile %d %d %d %d %d %d %d %d %d %d %d\n", i, map->tiles[i]->type,  map->tiles[i]->facing, map->tiles[i]->getWall(0),  map->tiles[i]->getWall(1),  map->tiles[i]->getWall(2) , map->tiles[i]->getWall(3) ,  map->tiles[i]->getLaser(0),  map->tiles[i]->getLaser(1),  map->tiles[i]->getLaser(2) , map->tiles[i]->getLaser(3) );
	}
	fclose(f);
}
void MapBuilder::loadFile(const char*fn)
{
	map->load(fn);
}

void MapBuilder::addObject()
{
	if (building_state != WALL || building_state != LASER)
		switch (rotation) {
		case 1:
			map->tiles[selectedTileX+selectedTileY*map->map_w]->facing  = Tile::NORTH;
			break;
		case 2:
			map->tiles[selectedTileX+selectedTileY*map->map_w]->facing  = Tile::EAST;
			break;
		case 3:
			map->tiles[selectedTileX+selectedTileY*map->map_w]->facing  = Tile::SOUTH;
			break;
		case 4:
			map->tiles[selectedTileX+selectedTileY*map->map_w]->facing  = Tile::WEST;
			break;
		}
	switch(building_state)
	{
	case EMPTY:
		map->tiles[selectedTileX+selectedTileY*map->map_w]->type = Tile::EMPTY;
		break;
	case STR_BELT:
		map->tiles[selectedTileX+selectedTileY*map->map_w]->type = Tile::STR_BELT;
		break;
	case LEFT_BELT:
		map->tiles[selectedTileX+selectedTileY*map->map_w]->type = Tile::LEFT_BELT;
		break;
	case RIGHT_BELT:
		map->tiles[selectedTileX+selectedTileY*map->map_w]->type = Tile::RIGHT_BELT;
		break;
	case UNI_BELT:
		map->tiles[selectedTileX+selectedTileY*map->map_w]->type = Tile::UNI_BELT;
		break;
	case STR_FAST_BELT:
		map->tiles[selectedTileX+selectedTileY*map->map_w]->type = Tile::STR_FAST_BELT;
		break;
	case LEFT_FAST_BELT:
		map->tiles[selectedTileX+selectedTileY*map->map_w]->type = Tile::LEFT_FAST_BELT;
		break;
	case RIGHT_FAST_BELT:
		map->tiles[selectedTileX+selectedTileY*map->map_w]->type = Tile::RIGHT_FAST_BELT;
		break;
	case UNI_FAST_BELT:
		map->tiles[selectedTileX+selectedTileY*map->map_w]->type = Tile::UNI_FAST_BELT;
		break;
	case LEFT_ROTATOR:
		map->tiles[selectedTileX+selectedTileY*map->map_w]->type = Tile::LEFT_ROTATOR;
		break;
	case RIGHT_ROTATOR:
		map->tiles[selectedTileX+selectedTileY*map->map_w]->type = Tile::RIGHT_ROTATOR;
		break;
	case HOLE:
		map->tiles[selectedTileX+selectedTileY*map->map_w]->type = Tile::HOLE;
		break;
	case REPAIR:
		map->tiles[selectedTileX+selectedTileY*map->map_w]->type = Tile::REPAIR;
		break;
	case MODIFY:
		map->tiles[selectedTileX+selectedTileY*map->map_w]->type = Tile::MODIFY;
		break;


	case WALL:

		switch (rotation) {
		case 1:
			map->tiles[selectedTileX+selectedTileY*map->map_w]->walls[rotation-1] = Tile::NORTH;
			break;
		case 2:
			map->tiles[selectedTileX+selectedTileY*map->map_w]->walls[rotation-1] = Tile::EAST;
			break;
		case 3:
			map->tiles[selectedTileX+selectedTileY*map->map_w]->walls[rotation-1] = Tile::SOUTH;
			break;
		case 4:
			map->tiles[selectedTileX+selectedTileY*map->map_w]->walls[rotation-1] = Tile::WEST;
			break;
		default:
			printf("rotation nemá správnou hodnotu %d \n", rotation);
			break;
		}

		break;
	case LASER:
		switch (rotation) {
		case 1:
			map->tiles[selectedTileX+selectedTileY*map->map_w]->lasers[rotation-1] = Tile::NORTH;
			break;
		case 2:
			map->tiles[selectedTileX+selectedTileY*map->map_w]->lasers[rotation-1] = Tile::EAST;
			break;
		case 3:
			map->tiles[selectedTileX+selectedTileY*map->map_w]->lasers[rotation-1] = Tile::SOUTH;
			break;
		case 4:
			map->tiles[selectedTileX+selectedTileY*map->map_w]->lasers[rotation-1] = Tile::WEST;
			break;
		default:
			printf("rotation nemá správnou hodnotu %d \n", rotation);
			break;
		}

		break;
	}

	createFile("maps/custom.txt");
	loadFile("maps/custom.txt");
}


void MapBuilder::keystate(Uint8* kst)
{

}
