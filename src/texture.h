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
	int x, y, variant_size;

	Obrazek *texture;
	Texture *texEmpty, *texHole, *texRotator, *texRepair, *texWall, *texLaser;
	Texture *texBeltStr, *texBeltLeft, *texBeltRight, *texBeltUni, *texBeltT;
	Texture *texFast_beltStr, *texFast_beltLeft, *texFast_beltRight, *texFast_beltUni, *texFast_beltT;
	Texture *texMove, *texRotate, *texHidden;
};

#endif // TEXTURE_H
