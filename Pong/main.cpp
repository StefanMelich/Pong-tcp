#pragma once
#include <iostream>
#include "Ball.h"
#include "Player.h"
#include "GameBoard.h"

using namespace std;


int main()
{

	GameBoard game(40, 20);
	game.run();

	return 0;
}
