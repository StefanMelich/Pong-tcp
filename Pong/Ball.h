#pragma once
#include <iostream>
#include "heap_monitor.h"
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
	void setX(int x);
	void setY(int y);
	DIRECTION getDirection();
	void rndLeft();
	void rndRight();
	void changeDirection(DIRECTION direction);
	void move();
	void wallChangeDir();
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

inline void Ball::setX(int x)
{
	_x = x;
}

inline void Ball::setY(int y)
{
	_y = y;
}

inline DIRECTION Ball::getDirection()
{
	return _direction;
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
		break;
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
	switch (_direction)
	{
	case UP_LEFT:
		_direction = DOWN_LEFT;
		break;
	case UP_RIGHT:
		_direction = DOWN_RIGHT;
		break;
	case DOWN_LEFT:
		_direction = UP_LEFT;
		break;
	case DOWN_RIGHT:
		_direction = UP_RIGHT;
		break;
	default:
		break;
	}	
}
