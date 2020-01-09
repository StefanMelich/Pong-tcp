#pragma once
#include <iostream>

#include "Server.h"
#include "Client.h"
#include "heap_monitor.h"

using namespace std;


int main()
{
	initHeapMonitor();

	int portNumber = 28176;
	
	char connectionType;
	cout << "s - server, c - client" << endl;
	cin >> connectionType;

	if (connectionType == 's')
	{
		Server server(portNumber);
		server.CreateServer();
	}
	else if (connectionType == 'c')
	{
		Client client(portNumber);
		client.Connect();
		//Client * client = new Client(portNumber);
		//client->Connect();
	}
	
	system("pause");
}
