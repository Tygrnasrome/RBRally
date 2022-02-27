#include "map.h"


Obrazovka* obrazoovka = Obrazovka::instance();

Map::Map()
{
	for (int i = 0;i<11;i++)
	{
		startingPos[i] = 0;
	}
	texture = new Texture();
	for (int i = 0;i<MAP_SIZE*MAP_SIZE;i++)
	{
		tiles[i] = new Tile();
		for(int c = 0 ; c<4 ; c ++)
		{
			tiles[i]->lasers[c] = Tile::NONE;
			tiles[i]->walls[c] = Tile::NONE;
			tiles[i]->addTexture(texture);

		}
	}
	map_h = 16;
	map_w = 12;
	map_size = map_h * map_w ;

	initX = initY = addedSize = 0;
}

Map::Map(const char*fn)
{
	texture = new Texture();
	for (int i = 0;i<MAP_SIZE*MAP_SIZE;i++)
	{
		tiles[i] = new Tile();
		for(int c = 0 ; c<4 ; c ++)
		{
			tiles[i]->lasers[c] = Tile::NONE;
			tiles[i]->walls[c] = Tile::NONE;
			tiles[i]->addTexture(texture);

		}
	}
	load(fn);
	map_size = map_h * map_w;
	initX = initY = 0;
}

void Map::load(const char*fn)
{
	map_h = map_w = 0;
	int object_size = 12;
	int d,  num = 0;
	int status = 0;
	int objects[object_size];
	for (int i = 0 ; i < object_size ; i ++)
	{
		objects[i] = 0;
	}
	FILE* f;

	f=fopen (fn, "r");
	std::string word;

	while (!feof(f))
	{

		/*precteni prvniho znaku a ulozeni do promenne
    "d"(c jako character)*/
		d=fgetc(f);
		//pokud fgetc precte konec souboru, prerusi cyklus a ukonci cteni
		if (feof(f))
			break;

		if (d == '\n')
		{
			status = 3;
		}
		switch (status)
		{
		case 0:
			if(d >= 'a'&& d <= 'z')
			{
				status = 1;
				ungetc(d, f);
				continue;
			}
			/*pokud porgram najde na zacatku slova neznamy znak
    ukonci se a vyhodi error */
			printf ("error: neznamy znak %d\n", d);
			return;
		case 1:
		{
			if (d== ' ')

				//pokud program najde konec slova (mezeru), zacne cist souradnice
			{
				//printf("%s", word.c_str()); (ověření, že je v proměnné word správná hodnota)
				status  = 2;
				num = 0;
				break;
			}
			if(!(d >= 'a'&& d <= 'z'))
				/*pokud porgram najde uprostred slova neznamy znak
    ukonci se a vyhodi error */
			{
				printf ("\nerror: neznamy znak\n");
				return;
			}
			//program cte jednotliva pismena
			word+= d;

			break;
		}
		case 2:
		{

			//pokud program najde konec slova (mezeru), zacne cist druhou cast souradnic
			if (d== ' ')
			{
				num++;
				if(num >= object_size)
				{
					status = 3;
				}

				break;
			}
			//program cte X hodnotu souradnic
			if(d >= '0'&& d <= '9')
			{
				objects[num] *= 10;
				objects[num] += d - '0';
				break;
			}

			//pokud dany znak neni cislo, program rovnou vyhodi error
			printf ("\nerror: neplatne cislo v souradnicich\n");
			return;
		}
		case 3:
		{

			if (word == "tile")
			{

				status = 0;
				word.clear();
				tiles[objects[0]]->setType(objects[1]);
				if(tiles[objects[0]]->type == Tile::STARTING_POS)
				{
					tiles[objects[0]]->starting_pos_num = objects[11];
					startingPos[objects[11]] = objects[0];
				}
				tiles[objects[0]]->setFacing(objects[2]);
				for(int i = 0 ; i < 4 ; i++)
					tiles[objects[0]]->addWall(i,objects[3+i]);
				for(int i = 0 ; i < 4 ; i++)
					tiles[objects[0]]->addLaser(i,objects[7+i]);
				for (int i = 0 ; i < object_size ; i ++)
				{
					objects[i] = 0;
				}
				break;
			}
			if (word == "maph")
			{

				status = 0;
				word.clear();
				map_h = objects[0];
				objects[0] = 0;
				break;
			}
			if (word == "mapw")
			{

				status = 0;
				word.clear();
				map_w = objects[0];
				objects[0] = 0;
				break;
			}
		}
		}
	}

}

void Map::place(int x, int y)
{
	initX = x;
	initY = y;
	this->x = (obrazoovka->w - map_w*TILE_SIZE)/2 + initX;
	this->y = (obrazoovka->h - map_h*TILE_SIZE)/2 + initY;
	for (int rada = 0 ; rada < map_h ; rada++)
	{
		for (int sloupec = 0 ; sloupec < map_w  ; sloupec++)
		{
			tiles[(rada*map_w)+sloupec]->x = sloupec*TILE_SIZE + this->x;
			tiles[(rada*map_w)+sloupec]->y = rada*TILE_SIZE + this->y;
		}
	}
}

void Map::draw()
{
	x = (obrazoovka->w - map_w*TILE_SIZE)/2 + initX;
	y = (obrazoovka->h - map_h*TILE_SIZE)/2 + initY;
	int rada = 0;
	int sloupec = 0;
	for (auto it = tile.begin(); it != tile.end(); it++)
	{

		if(sloupec == map_w)
		{
			rada++;
			sloupec = 0;
		}
		(*it)->draw(sloupec*TILE_SIZE + x ,rada*TILE_SIZE + y);
		(*it)->update();
		sloupec++;
	}
}

void Map::setWall(int id, int facing,int  num)
{
	switch (facing) {
	case 0:
		tiles[id]->walls[num] = Tile::NONE;
		break;
	case 1:
		tiles[id]->walls[num] = Tile::NORTH;
		break;
	case 2:
		tiles[id]->walls[num] = Tile::EAST;
		break;
	case 3:
		tiles[id]->walls[num] = Tile::SOUTH;
		break;
	case 4:
		tiles[id]->walls[num] = Tile::WEST;
		break;
	default:
		printf("neplatné číslo typu wall: %d, %d, %d\n", id, facing, num);
		break;
	}
}

void Map::setLaser(int id, int facing, int num)
{
	switch (facing) {
	case 0:
		tiles[id]->lasers[num] = Tile::NONE;
		break;
	case 1:
		tiles[id]->lasers[num] = Tile::NORTH;
		break;
	case 2:
		tiles[id]->lasers[num] = Tile::EAST;
		break;
	case 3:
		tiles[id]->lasers[num] = Tile::SOUTH;
		break;
	case 4:
		tiles[id]->lasers[num] = Tile::WEST;
		break;
	default:
		printf("neplatné číslo typu laser %d, %d, %d\n", id, facing, num);
		break;
	}
}

void Map::addMap(Map* map)
{
	for (int i = 0 ; i < map->map_h * map->map_w ; i++)
	{
		for (int num = 0; num < 11 ; num++)
			if (map->startingPos[num] != 0)
			{
				startingPos[num] = map->startingPos[num] + addedSize;
			}
		auto *t = map->tiles[i];
		tile.push_back(t);
	}
	addedSize += map->map_h * map->map_w;
	int number = 0;
	for (auto it = tile.begin(); it != tile.end(); it++)
	{
		(*it)->number = number;
		number++;
	}
}

void Map::setSize(int map_w, int map_h)
{
	this->map_h = map_h;
	this->map_w = map_w;
}

void Map::delMap()
{
	for (auto it = tile.begin(); it != tile.end(); it++)
	{
		delete *it;
		it = tile.erase(it);
		it--;
	}
}
void Map::boardMovement(Player *player)
{
	beltMovement(1, player);
	beltMovement(2, player);
	rotatorMovement(player);

	for(auto t = tile.begin(); t != tile.end(); t++)
	{
		if((*t)->occupied == player)
			printf("tile %d occupied \n", (*t)->number);
	}
}

void Map::beltMovement(int beltType, Player *player)
{
	bool end = false;
	int n = 0;
	for (auto it = tile.begin(); it != tile.end(); it++)
	{
		if((*it)->occupied != 0 && (*it)->occupied == player && end == false)
		{
			if(beltType == 1)
				if(	(*it)->type == Tile::STR_BELT || (*it)->type == Tile::LEFT_BELT ||
						(*it)->type == Tile::RIGHT_BELT || (*it)->type == Tile::UNI_BELT ||
						(*it)->type == Tile::STR_FAST_BELT || (*it)->type == Tile::LEFT_FAST_BELT ||
						(*it)->type == Tile::RIGHT_FAST_BELT || (*it)->type == Tile::UNI_FAST_BELT)
				{
					int tileFacing = 0;
					if((*it)->facing == Tile::NORTH) tileFacing = 1;
					if((*it)->facing == Tile::EAST) tileFacing = 2;
					if((*it)->facing == Tile::SOUTH) tileFacing = 3;
					if((*it)->facing == Tile::WEST) tileFacing = 4;
					(*it)->occupied->boardMove(1,this,tileFacing);
					end = true;
					for (auto t = tile.begin(); t != tile.end(); t++)
					{
						if((*t)->number == player->standingPos)
						{
							if(		(*t)->type == Tile::RIGHT_BELT ||
									(*t)->type == Tile::RIGHT_FAST_BELT )
							{
								player->rotate(1);
							}
							if(		(*t)->type == Tile::LEFT_BELT ||
									(*t)->type == Tile::LEFT_FAST_BELT )
							{
								player->rotate(-1);
							}
						}

					}
				}
			if(beltType == 2)
				if(		(*it)->type == Tile::STR_FAST_BELT || (*it)->type == Tile::LEFT_FAST_BELT ||
						(*it)->type == Tile::RIGHT_FAST_BELT || (*it)->type == Tile::UNI_FAST_BELT)
				{
					int tileFacing = 0;
					if((*it)->facing == Tile::NORTH) tileFacing = 1;
					if((*it)->facing == Tile::EAST) tileFacing = 2;
					if((*it)->facing == Tile::SOUTH) tileFacing = 3;
					if((*it)->facing == Tile::WEST) tileFacing = 4;
					(*it)->occupied->boardMove(1,this,tileFacing);
					end = true;
					for (auto t = tile.begin(); t != tile.end(); t++)
					{
						if((*t)->number == (*it)->occupied->standingPos)
						{
							if((*t)->type == Tile::RIGHT_FAST_BELT )
							{
								(*it)->occupied->rotate(1);
							}
							if((*t)->type == Tile::LEFT_FAST_BELT )
							{
								(*it)->occupied->rotate(-1);
							}
						}

					}
				}
			int num = 0;
			for(auto t = tile.begin(); t != tile.end(); t++)
			{
				if((*t)->occupied == player)
					(*t)->occupied = 0;
				if(num == player->standingPos)
				{

					if(!player->dead)
						(*t)->occupied = player;
				}
				num++;
			}
		}



		n++;
	}
}

void Map::rotatorMovement(Player *player)
{
	bool end = false;
	int n = 0;
	for (auto it = tile.begin(); it != tile.end(); it++)
	{
		if((*it)->occupied != 0 && (*it)->occupied == player && end == false)
		{
			if((*it)->type == Tile::LEFT_ROTATOR)
			{
				player->rotate(-1);
			}
			if((*it)->type == Tile::RIGHT_ROTATOR)
			{
				player->rotate(1);
			}
		}

	}
}

bool Map::laserShoot()
{
	bool end = false;
	int testTil, dir, h, w, n = 0;
	// init
	for (auto it = tile.begin(); it != tile.end(); it++)
		for(int i = 0 ; i < 4 ; i++)
			if((*it)->lasers[i] != 0)
			{

				end = false;
				switch ((*it)->lasers[i]) {
				case Tile::NORTH:
					dir = map_w;
					break;
				case Tile::EAST:
					dir = -1;
					break;
				case Tile::SOUTH:
					dir = -map_w;
					break;
				case Tile::WEST:
					dir = 1;
					break;
				}
				testTil = (*it)->number;
				h = testTil/map_w;
				w = (testTil+dir)%map_w;
				while(!end)
				{
					n = 0;
					h = (testTil+dir)/map_w;
					w = (testTil+dir)%map_w;
					if(h < 0 || h > map_h || w == 0 || w == map_w-1)
					{
						end = true;
					}
					switch ((*it)->lasers[i]) {
					case Tile::NORTH:
						for(auto t = tile.begin(); t != tile.end(); t++)
						{
							if(n == testTil)
							{
								if(testTil != (*it)->number)
									for(int i = 0; i != 4; i++)
									{
										if((*t)->walls[i] == Tile::NORTH)
										{
											end = true;
										}

									}
								if((*t)->occupied != 0)
								{
									if(!end)
									(*t)->occupied->takeDamage();
									end = true;
								}
								for(int i = 0; i != 4; i++)
								{
									if((*t)->walls[i] == Tile::SOUTH)
									{
										end = true;
									}
									if(!end)
										(*t)->addBeam(0);
								}

							}
							n++;
						}
						testTil += dir;
						break;
					case Tile::EAST:
						for(auto t = tile.begin(); t != tile.end(); t++)
						{
							if(n == testTil)
							{
								if(testTil != (*it)->number)



										for(int i = 0; i != 4; i++)
										{
											if((*t)->walls[i] == Tile::EAST)
											{
												end = true;
											}

										}

										if((*t)->occupied != 0)
										{
											if(!end)
											(*t)->occupied->takeDamage();
											end = true;
										}
										for(int i = 0; i != 4; i++)
										{
										if((*t)->walls[i] == Tile::WEST)
										{
											end = true;
										}
										if(!end)
											(*t)->addBeam(1);
									}
							}
							n++;
						}
						testTil += dir;
						break;
					case Tile::SOUTH:
						for(auto t = tile.begin(); t != tile.end(); t++)
						{
							if(n == testTil)
							{
								if(testTil != (*it)->number)
									for(int i = 0; i != 4; i++)
									{
										if((*t)->walls[i] == Tile::SOUTH)
										{
											end = true;
										}

									}
								if((*t)->occupied != 0)
								{
									if(!end)
									(*t)->occupied->takeDamage();
									end = true;
								}
								for(int i = 0; i != 4; i++)
								{
									if((*t)->walls[i] == Tile::NORTH)
									{
										end = true;
									}
									if(!end)
										(*t)->addBeam(2);
								}


							}
							n++;
						}
						testTil += dir;
						break;
					case Tile::WEST:
						for(auto t = tile.begin(); t != tile.end(); t++)
						{
							if(n == testTil)
							{

								if(testTil != (*it)->number)
									for(int i = 0; i != 4; i++)
									{
										if((*t)->walls[i] == Tile::WEST)
										{
											end = true;
										}

									}
								if((*t)->occupied != 0)
								{
									if(!end)
									(*t)->occupied->takeDamage();
									end = true;
								}
								for(int i = 0; i != 4; i++)
								{
									if((*t)->walls[i] == Tile::EAST)
									{
										end = true;
									}
									if(!end)
										(*t)->addBeam(3);
								}


							}
							n++;
						}
						testTil += dir;
						break;
					}
				}
			}
}

void Map::clearBeams()
{
	for(auto t = tile.begin(); t != tile.end(); t++)
	{
		(*t)->clearBeams();
	}
}

