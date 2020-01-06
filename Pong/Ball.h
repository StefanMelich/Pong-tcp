#pragma once
#include <iostream>
using namespace std;

enum DIRECTION { LEFT, RIGHT, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT };

class Ball
{
private:
	int _x;
	int _y;
	DIRECTION _direction;

public:
	Ball(int x, int y);
	~Ball();
	int getX();
	int getY();
	void rndLeft();
	void rndRight();
	void changeDirection(DIRECTION direction);
	void move();
	void wallChangeDir();

	friend ostream & operator<<(ostream & o, Ball ball)
	{
		o << "Ball [" << ball.getX() << ", " << ball.getY() << "]" << endl;
		return o;
	}

};

inline Ball::Ball(int x, int y)
{
	this->_x = x;
	this->_y = y;
}

inline Ball::~Ball() {}

inline int Ball::getX()
{
	return _x;
}

inline int Ball::getY()
{
	return _y;
}

inline void Ball::rndLeft()
{
	int i = (rand() % 3);
	if (i == 0)
		this->_direction = UP_LEFT;
	if (i == 1)
		this->_direction = LEFT;
	if (i == 2)
		this->_direction = DOWN_LEFT;
}

inline void Ball::rndRight()
{
	int i = (rand() % 3);
	if (i == 0)
		this->_direction = UP_RIGHT;
	if (i == 1)
		this->_direction = RIGHT;
	if (i == 2)
		this->_direction = DOWN_RIGHT;
}

inline void Ball::changeDirection(DIRECTION direction)
{
	this->_direction = direction;
}

inline void Ball::move()
{
	switch (_direction)
	{
	case UP_LEFT:
		_x--;
		_y--;
		break;
	case LEFT:
		_x--;
		break;
	case DOWN_LEFT:
		_x--;
		_y++;
		break;
	case UP_RIGHT:
		_x++;
		_y--;
		break;
	case RIGHT:
		_x++;
	case DOWN_RIGHT:
		_x++;
		_y++;
		break;
	default:
		break;
	}
}

inline void Ball::wallChangeDir()
{
	this->_y -= this->_y;
}
