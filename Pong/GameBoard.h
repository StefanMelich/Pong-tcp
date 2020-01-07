#pragma once
#include <iostream>
#include <conio.h>
#include "Player.h"
#include "Ball.h"

using namespace std;

class GameBoard
{
private:
	int width, height;
	char up, down;
	bool quit;
	Ball * ball;
	Player * player1;
	Player * player2;

	bool canDrawPlayer(int actualX, int actualY, int x, int y);

public:
	GameBoard(int w, int h);
	~GameBoard();
	void draw();
	void input();
	void collisionDetection();
	void run();
};

inline GameBoard::GameBoard(int w, int h)
{
	width = w;
	height = h;
	up = 'w';
	down = 's';
	quit = false;
	ball = new Ball(width / 2, height / 2);
	player1 = new Player(1, (height / 2) - 3);
	player2 = new Player(width - 2, (height / 2) - 3);
}

inline GameBoard::~GameBoard()
{
	delete ball, player1, player2;
}

inline void GameBoard::draw()
{
	system("cls"); // windows
	//system("clear"); // linux

	// vykresli gameboard
	for (int i = 0; i < width + 2; i++)
		cout << "\xB2";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int ballX = ball->getX();
			int ballY = ball->getY();
			int p1X = player1->getX();
			int p1Y = player1->getY();
			int p2X = player2->getX();
			int p2Y = player2->getY();

			// wall
			if (j == 0)
				cout << "\xB2";

			// ball
			if (ballX == j && ballY == i)
				cout << "O";

			//player1
			else if (canDrawPlayer(j, i, p1X, p1Y))
				cout << "\xDB";

			//player2
			else if (canDrawPlayer(j, i, p2X, p2Y))
				cout << "\xDB";

			// empty space
			else
				cout << " ";

			// wall
			if (j == width - 1)
				cout << "\xB2";
			
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "\xB2";
	cout << endl;
}

inline void GameBoard::input()
{
	ball->move();

	if (_kbhit())
	{
		char current = _getch();

		if (current == up)
		{
			if (player1->getY() > 0)
			{
				player1->moveUP();
			}
		}

		if (current == down)
		{
			if (player1->getY() + 4 < height)
			{
				player1->moveDOWN();
			}
		}

		if (current == 'q')
		{
			quit = true;
		}
	}
}

inline void GameBoard::collisionDetection()
{
	int ballX = ball->getX();
	int ballY = ball->getY();
	int p1X = player1->getX();
	int p1Y = player1->getY();

	// SERVER - left player 
	for (int i = 0; i < 4; i++)
	{
		if (ballX == p1X + 1)
		{
			if (ballY == p1Y + i)
			{
				ball->rndRight();
			}
		}
	}

	// CLIENT - right player
	// TODO: tcp 

	// ball hit wall bounce
	if (ballY == height - 1 || ballY == 0)
	{
		ball->wallChangeDir();
	}

	// ball hit wall game over
	//if (ballX == width - 1)


	//if (ballX == 0)

}

inline void GameBoard::run()
{
	while(!quit)
	{
		draw();
		input();
		collisionDetection();
	}
}

inline bool GameBoard::canDrawPlayer(int actualX, int actualY, int x, int y)
{
	if (actualX == x)
	{
		if (actualY == y || actualY == y + 1 || actualY == y + 2 || actualY == y + 3)
			return true;
	}
	return false;
}
