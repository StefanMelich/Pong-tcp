#pragma once
#include <iostream>
#include <conio.h>
//#include <unistd.h> posix
#include <Windows.h>
#include "Player.h"
#include "Ball.h" 
#include "heap_monitor.h"

using namespace std;

class GameBoard
{
private:
	int width, height;
	bool quit;
	Ball * ball;
	Player * player1;
	Player * player2;

	bool canDrawPlayer(int actualX, int actualY, int x, int y);
	

public:
	GameBoard(int w, int h);
	~GameBoard();
	bool isGameOver() { return quit; }
	int getBallX() { return ball->getX();  }
	int getBallY() { return ball->getY(); }
	int getPlayer1X() { return player1->getX(); }
	int getPlayer1Y() { return player1->getY(); }
	int getPlayer2X() { return player2->getX(); }
	int getPlayer2Y() { return player2->getY(); }
	void setPlayer1Y(int y) { this->player1->setY(y); }
	void setPlayer2Y(int y) { this->player2->setY(y); }
	void setBallX(int x) { this->ball->setX(x); }
	void setBallY(int y) { this->ball->setY(y); }
	void draw();
	void input();
	void collisionDetection();
	void run();
	bool wallGameOver();
};

inline GameBoard::GameBoard(int w, int h)
{
	width = w;
	height = h;
	quit = false;
	ball = new Ball(width / 2, height / 2);
	ball->changeDirection(LEFT);
	player1 = new Player(1, (height / 2) - 3);
	player2 = new Player(width - 2, (height / 2) - 3);
}

inline GameBoard::~GameBoard()
{
	delete ball;
	delete player1;
	delete player2;
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
	if (_kbhit())
	{
		char current = _getch();

		if (current == 'q')
			quit = true;

		// player1
		if (current == 'w')
			if (player1->getY() > 0)
				player1->moveUP();

		if (current == 's')
			if (player1->getY() + 4 < height)
				player1->moveDOWN();

		// player2
		if (current == 'u')
			if (player2->getY() > 0)
				player2->moveUP();

		if (current == 'j')
			if (player2->getY() + 4 < height)
				player2->moveDOWN();
	}
}

inline void GameBoard::collisionDetection()
{
	ball->move();

	int ballx = ball->getX();
	int bally = ball->getY();
	int player1x = player1->getX();
	int player2x = player2->getX();
	int player1y = player1->getY();
	int player2y = player2->getY();

	// SERVER - left player 
	for (int i = 0; i < 4; i++)
		if (ballx == player1x + 1)
			if (bally == player1y + i)
				ball->rndRight();

	// CLIENT - right player
	for (int i = 0; i < 4; i++)
		if (ballx == player2x - 1)
			if (bally == player2y + i)
				ball->rndLeft();

	// ball hit wall bounce
	if (bally == 0)
		ball->wallChangeDir();

	if (bally == height - 1)
		ball->wallChangeDir();

	// ball hit wall game over
	if (ballx == width - 1)
		quit = true;

	if (ballx == 0)
		quit = true;
}

inline bool GameBoard::wallGameOver()
{
	if (ball->getX() == width - 1)
		return true;

	if (ball->getX() == 0)
		return true;

	return false;
}


inline void GameBoard::run()
{
	while(!quit)
	{
		draw();
		input();
		collisionDetection();
		Sleep(50); // windows
		//usleep(50); // linux
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
