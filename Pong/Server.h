#pragma once
#include <SFML/Network.hpp>
#include <string>
#include <iostream>
#include "GameBoard.h"
#include "heap_monitor.h"

using namespace sf;

class Server
{
private:
	TcpListener listener;
	TcpSocket socket;
	GameBoard * game;
	int port;
	char dataBuffer[100];
	size_t received;

	void Game();
	void SendData();
	void ReceiveData();

public:
	Server(int port);
	~Server();
	void CreateServer();
	
};

inline Server::Server(int port)
{
	this->port = port;
}

inline Server::~Server()
{
	delete game;
}

inline void Server::CreateServer()
{
	listener.listen(port);
	listener.accept(socket);

	this->Game();
}

inline void Server::Game()
{
	game = new GameBoard(40, 20);
	// na zaciatku posiela server

	Thread drawT(&GameBoard::draw, game);
	Thread sendT(&Server::SendData, this);
	Thread receiveT(&Server::ReceiveData, this);

	while(!game->isGameOver())
	{
		drawT.launch();
		game->input();
		game->collisionDetection();

		sendT.launch();
		receiveT.launch();

		Sleep(100);
	}

	drawT.wait();

	system("cls");
	if (game->winner() == "p1")
		cout << "WINNER" << endl;
	else if (game->winner() == "p2")
		cout << "LOSER" << endl;
	else
		cout << "DRAW" << endl;
	
}

inline void Server::SendData()
{
	string message = "";
	message += to_string(game->getBallX()) + ",";
	message += to_string(game->getBallY()) + ",";
	message += to_string(game->getPlayer1Y());

	socket.send(message.c_str(), message.size() + 1);
}

inline void Server::ReceiveData()
{
	socket.receive(dataBuffer, sizeof(dataBuffer), received);
	if (received > 0)
	{
		// update player2 position
		int p2Y = stoi(dataBuffer);
		game->setPlayer2Y(p2Y);
	}
}