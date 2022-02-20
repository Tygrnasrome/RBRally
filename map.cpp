#include "map.h"


Obrazovka* obrazoovka = Obrazovka::instance();



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
	int object_size = 11;
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
}

void Map::draw()
{
	x = (obrazoovka->w - map_w*TILE_SIZE)/2 + initX;
	y = (obrazoovka->h - map_h*TILE_SIZE)/2 + initY;
	for (int rada = 0;rada<map_h;rada++)
	{
		for (int sloupec = 0;sloupec<map_w;sloupec++)
		{
			tiles[(rada*map_w)+sloupec]->draw(sloupec*TILE_SIZE + x ,rada*TILE_SIZE + y);
		}
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

void addMap(Map* map,const char*fn)
{

}
