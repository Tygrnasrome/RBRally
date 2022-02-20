#include "tile.h"


Tile::Tile()
{
	type = EMPTY;
	facing = NORTH;
	tile_size = TILE_SIZE;
	occupied = 0;
}
void Tile::addTexture(Texture *tex)
{
	this->tex = tex;
}

void Tile::draw(int x, int y)
{
	this->x = x;
	this->y = y;
	switch (type) {
	case EMPTY:
	case STARTING_POS:
		empty(x,y);
		break;
	case STR_BELT:
	case LEFT_BELT:
	case RIGHT_BELT:
	case UNI_BELT:
		belt(x,y);
		break;
	case STR_FAST_BELT:
	case LEFT_FAST_BELT:
	case RIGHT_FAST_BELT:
	case UNI_FAST_BELT:
	case T_FAST_BELT:
		fast_belt(x,y);
		break;
	case LEFT_ROTATOR:
		left_rotator(x,y);
		break;
	case RIGHT_ROTATOR:
		right_rotator(x,y);
		break;
	case HOLE:
		hole(x,y);
		break;
	case REPAIR:
		repair(x,y,0);
		break;
	case MODIFY:
		repair(x,y,1);
		break;
	case ERASE:
		empty(x,y);
		barva(CERVENA);
		bod(x,y);
		cara(x+TILE_SIZE, y+TILE_SIZE);
		bod(x+TILE_SIZE,y);
		cara(x,y+TILE_SIZE);
		break;
	default:
		printf("error - unmatching tile type");
		exit(1);
		return;
	}

	laser(x,y);
	wall(x,y);
	border(x,y);

}

void Tile::border(int x, int y)
{
	barva(50,50,50);
	bod(x,y);
	cara(x+tile_size,y);
	cara(x+tile_size,y+tile_size);
	cara(x,y+tile_size);
	cara(x,y);
}
void Tile::empty(int x, int y)
{

	tex->texEmpty->place(x,y);
	tex->texEmpty->draw(0);
}
void Tile::belt(int x, int y)
{
	switch (type) {
	case STR_BELT:
		tex->texBeltStr->place(x,y);
		switch (facing) {
		case NORTH:
			tex->texBeltStr->draw(0);
			break;
		case EAST:
			tex->texBeltStr->draw(1);
			break;
		case SOUTH:
			tex->texBeltStr->draw(2);
			break;
		case WEST:
			tex->texBeltStr->draw(3);
			break;
		default:
			printf("nesprávná orientace beltstr \n");
			break;
		}
		break;
	case LEFT_BELT:
		tex->texBeltLeft->place(x,y);
		switch (facing) {
		case NORTH:
			tex->texBeltLeft->draw(0);
			break;
		case EAST:
			tex->texBeltLeft->draw(1);
			break;
		case SOUTH:
			tex->texBeltLeft->draw(2);
			break;
		case WEST:
			tex->texBeltLeft->draw(3);
			break;
		default:
			printf("nesprávná orientace texBeltLeft \n");
			break;
		}
		break;
	case RIGHT_BELT:
		tex->texBeltRight->place(x,y);
		switch (facing) {
		case NORTH:
			tex->texBeltRight->draw(0);
			break;
		case EAST:
			tex->texBeltRight->draw(1);
			break;
		case SOUTH:
			tex->texBeltRight->draw(2);
			break;
		case WEST:
			tex->texBeltRight->draw(3);
			break;
		default:
			printf("nesprávná orientace texBeltRight \n");
			break;
		}
		break;
	case UNI_BELT:
		tex->texBeltUni->place(x,y);
		switch (facing) {
		case NORTH:
			tex->texBeltUni->draw(0);
			break;
		case EAST:
			tex->texBeltUni->draw(1);
			break;
		case SOUTH:
			tex->texBeltUni->draw(2);
			break;
		case WEST:
			tex->texBeltUni->draw(3);
			break;
		default:
			printf("nesprávná orientace texBeltUni \n");
			break;
		}
		break;
	default:
		printf("nesprávný typ belt \n");
		break;
	}

}
void Tile::fast_belt(int x, int y)
{
	switch (type) {
	case STR_FAST_BELT:
		tex->texFast_beltStr->place(x,y);
		switch (facing) {
		case NORTH:
			tex->texFast_beltStr->draw(0);
			break;
		case EAST:
			tex->texFast_beltStr->draw(1);
			break;
		case SOUTH:
			tex->texFast_beltStr->draw(2);
			break;
		case WEST:
			tex->texFast_beltStr->draw(3);
			break;
		default:
			printf("nesprávná orientace texFast_beltStr \n");
			break;
		}
		break;
	case LEFT_FAST_BELT:
		tex->texFast_beltLeft->place(x,y);
		switch (facing) {
		case NORTH:
			tex->texFast_beltLeft->draw(0);
			break;
		case EAST:
			tex->texFast_beltLeft->draw(1);
			break;
		case SOUTH:
			tex->texFast_beltLeft->draw(2);
			break;
		case WEST:
			tex->texFast_beltLeft->draw(3);
			break;
		default:
			printf("nesprávná orientace texFast_beltLeft \n");
			break;
		}
		break;
	case RIGHT_FAST_BELT:
		tex->texFast_beltRight->place(x,y);
		switch (facing) {
		case NORTH:
			tex->texFast_beltRight->draw(0);
			break;
		case EAST:
			tex->texFast_beltRight->draw(1);
			break;
		case SOUTH:
			tex->texFast_beltRight->draw(2);
			break;
		case WEST:
			tex->texFast_beltRight->draw(3);
			break;
		default:
			printf("nesprávná orientace texFast_beltRight \n");
			break;
		}
		break;
	case UNI_FAST_BELT:
		tex->texFast_beltUni->place(x,y);
		switch (facing) {
		case NORTH:
			tex->texFast_beltUni->draw(0);
			break;
		case EAST:
			tex->texFast_beltUni->draw(1);
			break;
		case SOUTH:
			tex->texFast_beltUni->draw(2);
			break;
		case WEST:
			tex->texFast_beltUni->draw(3);
			break;
		default:
			printf("nesprávná orientace texFast_beltUni \n");
			break;
		}
		break;
	default:
		printf("nesprávný typ belt \n");
		break;
	}
}
void Tile::left_rotator(int x, int y)
{
	tex->texRotator->place(x,y);
	tex->texRotator->draw(1);
}
void Tile::right_rotator(int x, int y)
{
	tex->texRotator->place(x,y);
	tex->texRotator->draw(0);
}
void Tile::repair(int x, int y, int type)
{
	tex->texRepair->place(x,y);
	tex->texRepair->draw(type);
}
void Tile::laser(int x, int y)
{

	int x1, y1;
	barva(221,122,121);
	for (int i = 0 ; i < 4; i++)
		switch (lasers[i]) {;
		case NORTH:
			x1 = TILE_SIZE/7*3;
			y1 = WALL_SIZE;
			tex->texLaser->place(x1+x,y1+y);
			tex->texLaser->draw(2);
			break;

		case SOUTH:
			x1 = TILE_SIZE/7*3;
			y1 = TILE_SIZE/5*4 - WALL_SIZE;
			tex->texLaser->place(x1+x,y1+y);
			tex->texLaser->draw(0);
			break;
		case WEST:
			x1 = WALL_SIZE;
			y1 = TILE_SIZE/7*3;
			tex->texLaser->place(x1+x,y1+y);
			tex->texLaser->draw(1);
			break;
		case EAST:
			x1 = TILE_SIZE/5*4 - WALL_SIZE;
			y1 = TILE_SIZE/7*3;
			tex->texLaser->place(x1+x,y1+y);
			tex->texLaser->draw(3);
			break;
		case NONE:
			break;
		default:

			printf("error - unmatching laser type");
			break;
		}
}

void Tile::wall(int x, int y)
{

	int x1;
	int x2;
	int y1;
	int y2;
	barva(235,216,63);
	for (int i = 0 ; i < 4; i++)
		switch (walls[i]) {;
		case NORTH:
			tex->texWall->place(x,y);
			tex->texWall->draw(0);
			break;

		case SOUTH:
			y1 = TILE_SIZE - WALL_SIZE;
			tex->texWall->place(x,y1+y);
			tex->texWall->draw(0);
			break;
		case WEST:
			tex->texWall->place(x,y);
			tex->texWall->draw(1);
			break;
		case EAST:
			x1 = TILE_SIZE - WALL_SIZE;
			tex->texWall->place(x + x1,y);
			tex->texWall->draw(1);
			break;
		case NONE:
			break;
		default:

			printf("error - unmatching wall type");
			break;
		}
}

void Tile::hole(int x, int y)
{
	tex->texHole->place(x,y);
	tex->texHole->draw(0);
}

void Tile::setType(int num)
{
	switch (num) {
	case 0:
		type = EMPTY;
		break;
	case 1:
		type = STR_BELT;
		break;
	case 2:
		type = LEFT_BELT;
		break;
	case 3:
		type = RIGHT_BELT;
		break;
	case 4:
		type = UNI_BELT;
		break;
	case 5:
		type = T_BELT;
		break;
	case 6:
		type = STR_FAST_BELT;
		break;
	case 7:
		type = LEFT_FAST_BELT;
		break;
	case 8:
		type = RIGHT_FAST_BELT;
		break;
	case 9:
		type = UNI_FAST_BELT;
		break;
	case 10:
		type = T_FAST_BELT;
		break;
	case 11:
		type = RIGHT_ROTATOR;
		break;
	case 12:
		type = LEFT_ROTATOR;
		break;
	case 13:
		type = HOLE;
		break;
	case 14:
		type = REPAIR;
		break;
	case 15:
		type = MODIFY;
		break;
	case 16:
		type = STARTING_POS;
		break;
	case 17:
		type = ERASE;
		break;
	default:
		printf("neplatné číslo typu tile %d", num);
		break;
	}
}
void Tile::setFacing(int num)
{
	switch (num) {
	case 0:
		facing = NONE;
		break;
	case 1:
		facing = NORTH;
		break;
	case 2:
		facing = EAST;
		break;
	case 3:
		facing = SOUTH;
		break;
	case 4:
		facing = WEST;
		break;

	default:
		printf("neplatné číslo typu facing %d", num);
		break;
	}
}

void Tile::addWall(int num, int facing)
{
	switch (facing) {
	case 0:
		walls[num] = NONE;
		break;
	case 1:
		walls[num] = NORTH;
		break;
	case 2:
		walls[num] = EAST;
		break;
	case 3:
		walls[num] = SOUTH;
		break;
	case 4:
		walls[num] = WEST;
		break;
	default:
		printf("neplatné číslo typu wall: %d %d\n", num, facing);
		break;
	}
}

void Tile::addLaser(int num, int facing)
{
	switch (facing) {
	case 0:
		lasers[num] = NONE;
		break;
	case 1:
		lasers[num] = NORTH;
		break;
	case 2:
		lasers[num] = EAST;
		break;
	case 3:
		lasers[num] = SOUTH;
		break;
	case 4:
		lasers[num] = WEST;
		break;
	default:
		printf("neplatné číslo typu laser %d %d\n", num, facing);
		break;
	}
}

int Tile::getWall(int id)
{

	switch (walls[id]) {
	case 0:
		return 0;
		break;
	case 1:
		return 1;
		break;
	case 2:
		return 2;
		break;
	case 3:
		return 3;
		break;
	case 4:
		return 4;
		break;
	}
}

int Tile::getLaser(int id)
{

	switch (lasers[id]) {
	case 0:
		return 0;
		break;
	case 1:
		return 1;
		break;
	case 2:
		return 2;
		break;
	case 3:
		return 3;
		break;
	case 4:
		return 4;
		break;
	}
}
