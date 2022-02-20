#ifndef PLAYER_H
#define PLAYER_H


class Player
{
public:
	Player(int x, int y);
	int x, y, rotation, r, g, b;
	int revivePos[2];
	void draw();
	void move();
	void rotate();
	void shoot();
};

#endif // PLAYER_H
