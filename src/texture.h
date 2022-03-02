#ifndef TEXTURE_H
#define TEXTURE_H
#include "grafika.h"

class Texture
{
public:
	Texture();
	Texture(const char *fn, int variant_size);
	void place(int x, int y);
	void draw(int variant);
	int x, y, variant_size, w ,h;

	Obrazek *texture;
};

#endif // TEXTURE_H
