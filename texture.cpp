#include "texture.h"

Texture::Texture(const char*path,int variant_size)
{
	x = y = 0;
	texture = new Obrazek[variant_size];

	for(int i = 0; i < variant_size; i++)
	{
		char str[100];
		sprintf(str, "%s%d.png", path, i);
		texture[i].nacti(str);
	}
	this->variant_size=variant_size;
}

Texture::Texture()
{
	texBeltStr = new Texture("textures/tiles/belt_straight/belt", 4);
	texBeltLeft = new Texture("textures/tiles/belt_left/belt", 4);
	texBeltRight = new Texture("textures/tiles/belt_right/belt", 4);
	texBeltUni = new Texture("textures/tiles/belt_unite/belt", 4);
	texFast_beltStr = new Texture("textures/tiles/fast_belt_straight/fast_belt", 4);
	texFast_beltLeft = new Texture("textures/tiles/fast_belt_left/fast_belt", 4);
	texFast_beltRight = new Texture("textures/tiles/fast_belt_right/fast_belt", 4);
	texFast_beltUni = new Texture("textures/tiles/fast_belt_unite/fast_belt", 4);
	texFast_beltT = new Texture("textures/tiles/fast_belt_t/fast_belt", 4);
	texEmpty = new Texture("textures/tiles/empty/empty", 1);
	texHole = new Texture("textures/tiles/hole/hole", 1);
	texRepair = new Texture("textures/tiles/repair/repair", 2);
	texRotator = new Texture("textures/tiles/rotator/rotator", 2);
	texWall = new Texture("textures/tiles/wall/wall", 2);
	texLaser = new Texture("textures/tiles/laser/laser", 4);
	texMove = new Texture("textures/cards/move", 4);
	texRotate = new Texture("textures/cards/rotate", 3);
	texHidden = new Texture("textures/cards/back", 1);
}

void Texture::place(int x, int y)
{
	for(int i = 0; i < variant_size; i++)
	{
		texture[i].umisti(x,y);
	}

}

void Texture::draw(int variant)
{
	texture[variant].kresli();
}
