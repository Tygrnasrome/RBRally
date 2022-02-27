#include "mapbuilder.h"

MapBuilder::MapBuilder()
{
	map = new Map("maps/custom.txt");
	draw_options = new Map("maps/draw_options.txt");
	example_tile = new Map();
	draw_options->setSize(5,4);
	draw_options->place(50, (obrazovka->h/2)-(2*TILE_SIZE));
	draw_options->addMap(draw_options);
	example_tile->setSize(1,1);
	example_tile->place(150, (obrazovka->h/2)-(2*TILE_SIZE));
	example_tile->addMap(example_tile);
	map->addMap(map);
	map->setSize(12,12);
	rotation = 1;
	for(int i = 0 ; i < 4 ; i ++)
	{
		walls[i] = 0;
	}
}
void MapBuilder::draw()
{
	map->draw();
	draw_options->draw();
	example_tile->draw();
	drawSelectingRect(0);
	drawSelectingRect(1);
}

void MapBuilder::drawSelectingRect(int id)
{

	barva(CERVENA);
	//červený obdélníček, kolem aktivního políčka
	if (id == 0)
	{
		if (selectedTileX < 0) selectedTileX = 0;
		if (selectedTileX >= map->map_w) selectedTileX = map->map_w -1;

		if (selectedTileY < 0) selectedTileY = 0;
		if (selectedTileY >= map->map_h) selectedTileY = map->map_h -1;
		obdelnik(selectedTileX*TILE_SIZE + map->x,selectedTileY*TILE_SIZE + map->y,(selectedTileX+1)*TILE_SIZE+1 + map->x,selectedTileY*TILE_SIZE+1 + map->y);
		obdelnik((selectedTileX+1)*TILE_SIZE + map->x,selectedTileY*TILE_SIZE + map->y,(selectedTileX+1)*TILE_SIZE+1 + map->x,(selectedTileY+1)*TILE_SIZE+1 + map->y);
		obdelnik(selectedTileX*TILE_SIZE + map->x,(selectedTileY+1)*TILE_SIZE + map->y,(selectedTileX+1)*TILE_SIZE+1 + map->x,(selectedTileY+1)*TILE_SIZE+1 + map->y);
		obdelnik(selectedTileX*TILE_SIZE + map->x,selectedTileY*TILE_SIZE + map->y,selectedTileX*TILE_SIZE+1 + map->x,(selectedTileY+1)*TILE_SIZE+1 + map->y);
	}
	if (id == 1)
	{
		if (selTypeTileX < 0) selTypeTileX = 0;
		if (selTypeTileX >= draw_options->map_w) selTypeTileX = draw_options->map_w -1;

		if (selTypeTileY < 0) selTypeTileY = 0;
		if (selTypeTileY >= draw_options->map_h) selTypeTileY = draw_options->map_h -1;
		obdelnik(selTypeTileX*TILE_SIZE + draw_options->x,selTypeTileY*TILE_SIZE + draw_options->y,(selTypeTileX+1)*TILE_SIZE+1 + draw_options->x,selTypeTileY*TILE_SIZE+1 + draw_options->y);
		obdelnik((selTypeTileX+1)*TILE_SIZE + draw_options->x,selTypeTileY*TILE_SIZE + draw_options->y,(selTypeTileX+1)*TILE_SIZE+1 + draw_options->x,(selTypeTileY+1)*TILE_SIZE+1 + draw_options->y);
		obdelnik(selTypeTileX*TILE_SIZE + draw_options->x,(selTypeTileY+1)*TILE_SIZE + draw_options->y,(selTypeTileX+1)*TILE_SIZE+1 + draw_options->x,(selTypeTileY+1)*TILE_SIZE+1 + draw_options->y);
		obdelnik(selTypeTileX*TILE_SIZE + draw_options->x,selTypeTileY*TILE_SIZE + draw_options->y,selTypeTileX*TILE_SIZE+1 + draw_options->x,(selTypeTileY+1)*TILE_SIZE+1 + draw_options->y);
	}

}
void MapBuilder::update()
{
	setBuildingState();
	draw_options->place(-550, (obrazovka->h/4)-(4*TILE_SIZE));
	example_tile->place(-550, (obrazovka->h/4)-(8*TILE_SIZE));
}

void MapBuilder::setBuildingState()
{
	if(selTypeTileX == 0 && selTypeTileY == 0)
		building_state = EMPTY;
	if(selTypeTileX == 1 && selTypeTileY == 0)
		building_state = STR_BELT;
	if(selTypeTileX == 1 && selTypeTileY == 1)
		building_state = RIGHT_BELT;
	if(selTypeTileX == 1 && selTypeTileY == 2)
		building_state = LEFT_BELT;
	if(selTypeTileX == 1 && selTypeTileY == 3)
		building_state = UNI_BELT;
	if(selTypeTileX == 2 && selTypeTileY == 0)
		building_state = STR_FAST_BELT;
	if(selTypeTileX == 2 && selTypeTileY == 1)
		building_state = RIGHT_FAST_BELT;
	if(selTypeTileX == 2 && selTypeTileY == 2)
		building_state = LEFT_FAST_BELT;
	if(selTypeTileX == 2 && selTypeTileY == 3)
		building_state = UNI_FAST_BELT;
	if(selTypeTileX == 0 && selTypeTileY == 1)
		building_state = RIGHT_ROTATOR;
	if(selTypeTileX == 0 && selTypeTileY == 2)
		building_state = LEFT_ROTATOR;
	if(selTypeTileX == 0 && selTypeTileY == 3)
		building_state = HOLE;
	if(selTypeTileX == 3 && selTypeTileY == 0)
		building_state = WALL;
	if(selTypeTileX == 3 && selTypeTileY == 1)
		building_state = LASER;
	if(selTypeTileX == 3 && selTypeTileY == 2)
		building_state = REPAIR;
	if(selTypeTileX == 3 && selTypeTileY == 3)
		building_state = MODIFY;
	if(selTypeTileX == 4 && selTypeTileY == 0)
		building_state = ERASE;
}
void MapBuilder::event(SDL_Event* e)
{
	switch(e->type)
	{
	case SDL_KEYDOWN:
		switch(e->key.keysym.sym)
		{
		/* změna building_state */

		case SDLK_r:
			rotation++;
			if(rotation == 5)
				rotation = 1;
			erase(example_tile);
			update();
			addObject(example_tile);
			break;


		case SDLK_LEFT:
			changeSize(-1,0);
			break;
		case SDLK_RIGHT:
			changeSize(1,0);
			break;
		case SDLK_UP:
			changeSize(0,1);
			break;
		case SDLK_DOWN:
			changeSize(0,-1);
			break;

		case SDLK_a:
			selTypeTileX--;
			erase(example_tile);
			update();
			drawSelectingRect(1);
			addObject(example_tile);
			break;
		case SDLK_d:
			selTypeTileX++;
			erase(example_tile);
			update();
			drawSelectingRect(1);
			addObject(example_tile);
			break;
		case SDLK_w:
			selTypeTileY--;
			erase(example_tile);
			update();
			drawSelectingRect(1);
			addObject(example_tile);
			break;
		case SDLK_s:
			selTypeTileY++;
			erase(example_tile);
			update();
			drawSelectingRect(1);
			addObject(example_tile);
			break;

			/* renderování .txt souboru */

		}
		break;
	case SDL_MOUSEMOTION:
	{
		selectedTileX = e->motion.x / TILE_SIZE - map->x/ TILE_SIZE;
		selectedTileY = e->motion.y / TILE_SIZE - map->y/ TILE_SIZE;
		drawSelectingRect(0);
		break;
	}
	case SDL_MOUSEBUTTONDOWN:
	{
		addObject(map);
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
	map->delMap();
	map->addMap(map);
}

void MapBuilder::erase(Map *map)
{
	int yPos = 0;
	int xPos = 0;
	if(map->map_h != 1 && map->map_w != 1)
	{
		xPos = selectedTileX;
		yPos = selectedTileY;
	}
	for(int i = 0 ; i<4 ; i++)
		map->tiles[xPos+yPos*map->map_w]->walls[i] = Tile::NONE;
	for(int i = 0 ; i<4 ; i++)
		map->tiles[xPos+yPos*map->map_w]->lasers[i] = Tile::NONE;

	map->tiles[xPos+yPos*map->map_w]->type = Tile::EMPTY;
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

void MapBuilder::addObject(Map *map)
{
	int yPos = 0;
	int xPos = 0;
	if(map->map_h != 1 && map->map_w != 1)
	{
		xPos = selectedTileX;
		yPos = selectedTileY;
	}
	if (building_state != WALL && building_state != LASER)
		switch (rotation) {
		case 1:
			map->tiles[xPos+yPos*map->map_w]->facing  = Tile::NORTH;
			break;
		case 2:
			map->tiles[xPos+yPos*map->map_w]->facing  = Tile::EAST;
			break;
		case 3:
			map->tiles[xPos+yPos*map->map_w]->facing  = Tile::SOUTH;
			break;
		case 4:
			map->tiles[xPos+yPos*map->map_w]->facing  = Tile::WEST;
			break;
		}
	switch(building_state)
	{
	case EMPTY:
		map->tiles[xPos+yPos*map->map_w]->type = Tile::EMPTY;
		break;
	case STR_BELT:
		map->tiles[xPos+yPos*map->map_w]->type = Tile::STR_BELT;
		break;
	case LEFT_BELT:
		map->tiles[xPos+yPos*map->map_w]->type = Tile::LEFT_BELT;
		break;
	case RIGHT_BELT:
		map->tiles[xPos+yPos*map->map_w]->type = Tile::RIGHT_BELT;
		break;
	case UNI_BELT:
		map->tiles[xPos+yPos*map->map_w]->type = Tile::UNI_BELT;
		break;
	case STR_FAST_BELT:
		map->tiles[xPos+yPos*map->map_w]->type = Tile::STR_FAST_BELT;
		break;
	case LEFT_FAST_BELT:
		map->tiles[xPos+yPos*map->map_w]->type = Tile::LEFT_FAST_BELT;
		break;
	case RIGHT_FAST_BELT:
		map->tiles[xPos+yPos*map->map_w]->type = Tile::RIGHT_FAST_BELT;
		break;
	case UNI_FAST_BELT:
		map->tiles[xPos+yPos*map->map_w]->type = Tile::UNI_FAST_BELT;
		break;
	case LEFT_ROTATOR:
		map->tiles[xPos+yPos*map->map_w]->type = Tile::LEFT_ROTATOR;
		break;
	case RIGHT_ROTATOR:
		map->tiles[xPos+yPos*map->map_w]->type = Tile::RIGHT_ROTATOR;
		break;
	case HOLE:
		map->tiles[xPos+yPos*map->map_w]->type = Tile::HOLE;
		break;
	case REPAIR:
		map->tiles[xPos+yPos*map->map_w]->type = Tile::REPAIR;
		break;
	case MODIFY:
		map->tiles[xPos+yPos*map->map_w]->type = Tile::MODIFY;
		break;
	case ERASE:
		erase(map);
		break;


	case WALL:

		switch (rotation) {
		case 1:
			map->tiles[xPos+yPos*map->map_w]->walls[rotation-1] = Tile::NORTH;
			break;
		case 2:
			map->tiles[xPos+yPos*map->map_w]->walls[rotation-1] = Tile::EAST;
			break;
		case 3:
			map->tiles[xPos+yPos*map->map_w]->walls[rotation-1] = Tile::SOUTH;
			break;
		case 4:
			map->tiles[xPos+yPos*map->map_w]->walls[rotation-1] = Tile::WEST;
			break;
		default:
			printf("rotation nemá správnou hodnotu %d \n", rotation);
			break;
		}

		break;
	case LASER:
		switch (rotation) {
		case 1:
			map->tiles[xPos+yPos*map->map_w]->lasers[rotation-1] = Tile::NORTH;
			break;
		case 2:
			map->tiles[xPos+yPos*map->map_w]->lasers[rotation-1] = Tile::EAST;
			break;
		case 3:
			map->tiles[xPos+yPos*map->map_w]->lasers[rotation-1] = Tile::SOUTH;
			break;
		case 4:
			map->tiles[xPos+yPos*map->map_w]->lasers[rotation-1] = Tile::WEST;
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
