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
	w = texture[0].w;
	h = texture[0].h;
}

Texture::Texture()
{

}

void Texture::place(int x, int y)
{
	this->x = x;
	this->y = y;
	for(int i = 0; i < variant_size; i++)
	{
		texture[i].umisti(x,y);
	}

}

void Texture::draw(int variant)
{
	texture[variant].kresli();
}
