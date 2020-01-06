#pragma once
#include <iostream>

using namespace std;

class Player
{
private:
	int x, y;

public:
	Player(int posX, int posY);
	int getX();
	int getY();

	void moveUP();
	void moveDOWN();

	friend ostream & operator<<(ostream & o, Player p)
	{
		o << "Player [" << p.getX() << ", " << p.getY() << "]" << endl;
		return o;
	}
};

inline Player::Player(int posX, int posY)
{
	x = posX;
	y = posY;
}

inline int Player::getX()
{
	return x;
}

inline int Player::getY()
{
	return y;
}

inline void Player::moveUP()
{
	y--;
}

inline void Player::moveDOWN()
{
	y++;
}
