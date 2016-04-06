#include "ClientList.h"

/******************************************
ClientList.h - This class uses a linked list to hold Client objects. 

Author:		Adam Allard
Created:	06/10/15 - Initial
Revisions:
*******************************************/

ClientList::ClientList()
{
	head = nullptr;
}

ClientList:: ~ClientList()
{
	ClientNode* tempPtr;
	while (head != nullptr)
	{
		tempPtr = head;
		head = head->next;
		delete tempPtr;
	}
}

void ClientList::newClient(Client person)
{
	ClientNode* nodePtr;
	ClientNode* newNode;
	newNode = new ClientNode;
	newNode->member = person;
	newNode->next = NULL;
	if (!head)
		head = newNode;
	else
	{
		nodePtr = head;
		while (nodePtr->next)
			nodePtr = nodePtr->next;
		nodePtr->next = newNode;
	}
}

void ClientList::unmatchClient(Client &person)
{
	ClientNode *nodePtr = head;
	string str = "";
	while (nodePtr != nullptr)
	{
		if (nodePtr->member.getName() == person.getName())
		{
			nodePtr->member.setMatch(str);
		}
		nodePtr = nodePtr->next;
	}
}

// prints all individuals who do not have a match
string ClientList::printFree()
{
	string rtn;
	ClientNode* nodePtr = head;
	while (nodePtr != nullptr)
	{
		if (nodePtr->member.getMatch() == "")
		{
			rtn += nodePtr->member.getClientInfo() + "\n";
		}
		nodePtr = nodePtr->next;
	}
	return rtn;
}

// prints all pairs who have matches
string ClientList::printMatched()
{
	string rtn;
	ClientNode* nodePtr = head;
	while (nodePtr != nullptr)
	{
		if (nodePtr->member.getMatch() != "")
		{
			rtn += nodePtr->member.getName() + " - "
				+ nodePtr->member.getMatch() + "\n";
		}
		nodePtr = nodePtr->next;
	}
	return rtn;
}

// finds a match the client passed as a parameter
//		uses the .matchClient method from the Client class
void ClientList::findMatch(Client &client)
{
	ClientNode* nodePtr = head;

	while (nodePtr != nullptr)
	{
		nodePtr->member.matchClient(client);
		nodePtr = nodePtr->next;
	}
}

// finds a certain Client in the list using the name
Client ClientList::findClient(string name)
{
	ClientNode *nodePtr = head;
	Client client;

	while (nodePtr != nullptr)
	{
		if (nodePtr->member.getName() == name)
		{
			client.setName(nodePtr->member.getName());
			client.setPhoneNumber(nodePtr->member.getPhoneNumber());
			client.setMatch(nodePtr->member.getMatch());

			return client;
		}
		nodePtr = nodePtr->next;
	}
}