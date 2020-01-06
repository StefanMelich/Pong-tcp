#pragma once
#include <iostream>
#include "Ball.h"
#include "Player.h"
#include "GameBoard.h"

using namespace std;


int main()
{
	/*
	Ball ball(0, 0);
	cout << ball << endl;
	ball.rndLeft();
	ball.move();
	cout << ball << endl;
	ball.move();
	cout << ball << endl;
	ball.rndRight();
	ball.move();
	cout << ball << endl;
	*/

	/*
	Player p1(0, 0);
	Player p2(10, 0);
	cout << p1 << endl;
	cout << p2 << endl;
	p1.moveUP();
	p2.moveDOWN();
	cout << p1 << endl;
	cout << p2 << endl;
	*/

	GameBoard game(40, 20);
	game.draw();

	return 0;
}
