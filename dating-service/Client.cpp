#include "Client.h"

/******************************************
Client.h - This class holds information about a client 
				including sex, name, phone number, interest, and
				if they have a compatible match or not

Author:		Adam Allard
Created:	06/10/15 - Initial
Revisions:
*******************************************/

Client::Client()
{ 

}

void Client::setSex(char s)
	{ sex = s; }

void Client::setName(string n)
	{ name = n; }

void Client::setPhoneNumber(string p)
	{ phoneNumber = p; }

void Client::setInterests(string intStr, int intIndex)
{
	interest[intIndex] = intStr;
}

// this method checks every interest of a client with every 
//		interest of another client to see if they have the same
//		interests. if so (besides an empty string) then timesFound 
//		integer is incremented. if more than 3 or more interests are found
//		then the two become a match and both matches are changed to eachother
void Client::matchClient(Client &otherClient)
{
	int timesFound = 0;

	for (int memberIndex = 0; memberIndex < 10; memberIndex++)
	{
		for (int otherIndex = 0; otherIndex < 10; otherIndex++)
		{
			if (interest[memberIndex] == otherClient.interest[otherIndex])
			{
				if (interest[memberIndex] != "")
				{
					timesFound++;
				}
			}
		}
	}
	if (timesFound > 2)
	{
		match = otherClient.getName();
		otherClient.setMatch(name);
	}
}

void Client::setMatch(string m)
	{ match = m; }

// getters

char Client::getSex() const
	{ return sex; }

string Client::getName() const
	{ return name; }

string Client::getPhoneNumber() const
	{ return phoneNumber; }

string Client::getClientInfo() const
{
	string description;
	description = "Name: " + name + " #: " + phoneNumber;
	return description;
}

int Client::getNumInterests() const
	{ return numInterest; }

string Client::getMatch() const
	{ return match; }