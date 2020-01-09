#pragma once
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <string>
#include <iostream>
#include <thread>
#include "GameBoard.h"
#include "heap_monitor.h"

using namespace sf;

class Client
{
private:
	TcpListener listener;
	TcpSocket socket;
	IpAddress ip;
	GameBoard * game;
	int port;
	char mode;
	char dataBuffer[100];
	size_t received;

	void Game();
	void SendData();
	void ReceiveData();

public:
	Client(int port);
	~Client();
	void Connect();
};

inline Client::Client(int port)
{
	this->port = port;
	ip = IpAddress::getLocalAddress();
}

inline Client::~Client()
{
	delete game;
}

inline void Client::Connect()
{
	socket.connect(ip, port);

	this->Game();
}

inline void Client::Game()
{
	game = new GameBoard(40, 20);

	Thread drawT(&GameBoard::draw, game);
	Thread sendT(&Client::SendData, this);
	Thread receiveT(&Client::ReceiveData, this);

	while (!game->wallGameOver())
	{
		drawT.launch();
		game->input();

		receiveT.launch();
		sendT.launch();
		
		Sleep(100);
	}

	drawT.wait();

	system("cls");
	if (game->winner() == "p1")
		cout << "LOSER" << endl;
	else if (game->winner() == "p2")
		cout << "WINER" << endl;
	else
		cout << "DRAW" << endl;
}

inline void Client::SendData()
{
	string message = to_string(game->getPlayer2Y());

	socket.send(message.c_str(), message.size() + 1);
}

inline void Client::ReceiveData()
{
	socket.receive(dataBuffer, sizeof(dataBuffer), received);
	if (received > 0)
	{
		// update ball and player1 position
		string response = "";
		for(int i = 0; i < received; i++)
		{
			response += dataBuffer[i];
		}

		string delimiter = ",";
		size_t position = 0;

		position = response.find(delimiter);
		int ballX = stoi(response.substr(0, position));
		response.erase(0, position + delimiter.length());

		position = response.find(delimiter);
		int ballY = stoi(response.substr(0, position));
		response.erase(0, position + delimiter.length());

		int p1Y = stoi(response);

		game->setPlayer1Y(p1Y);
		game->setBallX(ballX);
		game->setBallY(ballY);
	}
}
