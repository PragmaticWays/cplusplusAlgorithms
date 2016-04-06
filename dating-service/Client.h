#ifndef CLIENT_H
#define CLIENT_H
#include <string>
using namespace std;

/******************************************
Client.h -  This class holds information about a client 
				including sex, name, phone number, interest, and
				if they have a compatible match or not

Author:		Adam Allard
Created:	06/10/15 - Initial
Revisions:
*******************************************/

class Client
{
private:
	char sex;
	string name;
	string phoneNumber;
	int numInterest;
	string interest[10];
	string match;

public:
	Client();
	void setSex(char);
	void setName(string);
	void setPhoneNumber(string);
	void setInterests(string, int);
	void matchClient(Client&);
	void setMatch(string);

	char getSex() const;
	string getName() const;
	string getPhoneNumber() const;
	string getClientInfo() const;
	int getNumInterests() const;
	string getMatch() const;

	void operator=(const Client &right)
	{
		name = right.name;
		sex = right.sex;
		phoneNumber = right.phoneNumber;
		numInterest = right.numInterest;
		match = right.match;
		for (int i = 0; i < 10; i++)
		{
			interest[i] = right.interest[i];
		}
	}
};
#endif