#pragma once
#include <iostream>
#include "Player.h"
#include "Ball.h"

using namespace std;

class GameBoard
{
private:
	int width, height;
	Ball * ball;
	Player * player1;
	Player * player2;

public:
	GameBoard(int w, int h);
	~GameBoard();
	void draw();

};

inline GameBoard::GameBoard(int w, int h)
{
	width = w;
	height = h;
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

			// player1
			else if (p1X == j && p1Y == i)
				cout << "\xDB";

			// player2
			else if (p2X == j && p2Y == i)
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



