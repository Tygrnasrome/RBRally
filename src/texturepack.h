#ifndef TEXTUREPACK_H
#define TEXTUREPACK_H
#include "texture.h"

class TexturePack : public Texture
{
public:
	TexturePack();
	Texture *texEmpty, *texHole, *texRotator, *texRepair, *texWall, *texLaser;
	Texture *texBeltStr, *texBeltLeft, *texBeltRight, *texBeltUni, *texBeltT;
	Texture *texFast_beltStr, *texFast_beltLeft, *texFast_beltRight, *texFast_beltUni, *texFast_beltT;
	Texture *texMove, *texRotate, *texHidden;
	Texture *texPlayerUI;
};

#endif // TEXTUREPACK_H
