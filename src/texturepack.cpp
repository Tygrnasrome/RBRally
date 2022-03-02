#include "texturepack.h"

TexturePack::TexturePack():Texture::Texture()
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
	texMove = new Texture("textures/cards/little/move", 4);
	texRotate = new Texture("textures/cards/little/rotate", 3);
	texHidden = new Texture("textures/cards/little/back", 1);
	texPlayerUI = new Texture("textures/banners/playerUI", 1);
}
