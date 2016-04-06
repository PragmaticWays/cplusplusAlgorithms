#ifndef CLIENTLIST_H
#define CLIENTLIST_H
#include <string>
#include <iostream>
#include "Client.h"
using namespace std;


/******************************************
ClientList.h - This class uses a linked list to hold client objects.

Author:		Adam Allard
Created:	06/10/15 - Initial
Revisions:
*******************************************/

class ClientList
{
private:

	struct ClientNode
	{
		Client member;
		struct ClientNode *next;
	};

	ClientNode *head;

public:
	ClientList();
	~ClientList();

	void newClient(Client);
	void unmatchClient(Client&);
	string printFree();
	string printMatched();
	void findMatch(Client&);
	
	Client findClient(string);

};
#endif