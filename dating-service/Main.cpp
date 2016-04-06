#include "Client.h"
#include "ClientList.h"
#include "Tee.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// used to echo print to screen and file.
// could not get it to work with Dates.out... don't know why
ofstream outFile("Dates.txt");
Tee echoPrint(std::cout, outFile);

void readCurrentClients(ClientList*, ClientList*);
int menu();
void newClient(ClientList*, ClientList*);
void unmatch(ClientList*);
void printMatch(ClientList*);
void printFree(ClientList*, ClientList*);

/******************************************
Dating Service - This program is a computer dating service. 
	Each client gives you his or her name, phone number, and a 
	list of interests. This program maintains lists of men 
	and women using the service and to match up the compatible 
	couples.

Author:		Adam Allard
Created:	06/10/15 - Initial
Revisions:	
*******************************************/

int main()
{
	// create a male list and a female list, and their respective pointers
	ClientList maleList;
	ClientList *maleListPtr;
	maleListPtr = &maleList;

	ClientList femaleList;
	ClientList *femaleListPtr;
	femaleListPtr = &femaleList;

	// read in current clients and add them to the male/female lists
	readCurrentClients(maleListPtr, femaleListPtr);

	// return value (int) from menu function is used for switch case 
	//     to transfer from menu to respective functions
	int menuChoice;
	do
	{
		menuChoice = menu();
		switch (menuChoice)
		{
			// adds new client
		case 1:
			newClient(maleListPtr, femaleListPtr);
			echoPrint << "\n";
			break;

			// unmatches clients from their match
		case 2:
			char sex;
			echoPrint << "Are you male or female? Enter M or F: ";
			cin >> sex;
			outFile << sex;

			while (sex != 'M' && sex != 'F')
			{
				echoPrint << "We apologize, this site is only for males and females.\n"
					<< "Please enter M or F: ";
				cin >> sex;
				outFile << sex;
			}

			if (sex == 'M')
				unmatch(maleListPtr);
			else if (sex == 'F')
				unmatch(femaleListPtr);

			echoPrint << "\n";
			break;

			// prints the matched pairs
		case 3:
			printMatch(maleListPtr);
			echoPrint << "\n";
			break;

			// prints the lonely unmatched individuals
		case 4:
			printFree(maleListPtr, femaleListPtr);
			echoPrint << "\n";
			break;
		} 
	} while (menuChoice != 5);

	echoPrint << "\n";
	system("pause");
	return 0;
}

// functions reads in current clients from Clients.mf and adds them to their respective list
void readCurrentClients(ClientList *maleList, ClientList *femaleList)
{
	ifstream currentClients;
	string str;
	Client newMember;
	currentClients.open("Clients.mf", ios::in);

	if (currentClients)
	{
		do
		{
			// sex
			getline(currentClients, str, ' ');
			char sex = str[0];
			newMember.setSex(sex);

			// name
			getline(currentClients, str, ',');
			newMember.setName(str);

			// phone number
			getline(currentClients, str, ' ');
			getline(currentClients, str, ' ');
			newMember.setPhoneNumber(str);

			// number of interests
			getline(currentClients, str, ' ');
			int num = stoi(str, nullptr, 10);

			// reset interests
			for (int i = 0; i < 10; i++)
			{
				str = "";
				newMember.setInterests(str, i);
			}

			// input interests
			for (int i = 0; i < num; i++)
			{
				getline(currentClients, str, ',');
				newMember.setInterests(str, i);
				getline(currentClients, str, ' ');
			}

			// match
			getline(currentClients, str, '\n');
			newMember.setMatch(str);

			// add to appropriate list
			if (sex == 'M')
			{
				maleList->newClient(newMember);
			}
			else if (sex == 'F')
			{
				femaleList->newClient(newMember);
			}
		} while (!currentClients.eof());
	}
	currentClients.close();
}

// menu function returns an int to be passed back into switch case in main()
int menu()
{
	int choice;

	for (int i = 0; i < 19; i++)
		echoPrint << char(3);
	echoPrint << "\n";
	echoPrint << "Dating Service Menu\n" 
		<< "1. New Client\n" 
		<< "2. Unmatch Client\n" 
		<< "3. Print Matches\n" 
		<< "4. Print Non-Matches\n" 
		<< "5. Quit\n";
	echoPrint << "Enter your choice (1-5): ";
	cin >> choice;
	outFile << choice;
	echoPrint << "\n";

	while (choice < 1 || choice > 5)
	{
		echoPrint << "Invalid choice. Reenter (1-5): ";
		cin >> choice;
		outFile << choice;
		echoPrint << "\n";
	}
	return choice;
}

// adds new client
void newClient(ClientList *maleList, ClientList *femaleList)
{
	Client newMember;
	string str;
	char memberSex;
	int numIntrests;

	cin.ignore();
	echoPrint << "Sex (Enter M or F): ";
	cin >> memberSex;
	outFile << memberSex;

	while (memberSex != 'M' && memberSex != 'F')
	{
		echoPrint << "We apologize, this site is only for males and females.\n"
			<< "Please enter M or F: ";
		cin >> memberSex;
		outFile << memberSex;
	}
	newMember.setSex(memberSex);

	cin.ignore();
	echoPrint << "Name: ";
	getline(cin, str);
	outFile << str;
	newMember.setName(str);

	echoPrint << "Phone Number: ";
	getline(cin, str);
	outFile << str;
	newMember.setPhoneNumber(str);

	echoPrint << "Number of Interests: ";
	cin >> numIntrests;
	outFile << numIntrests;

	while (numIntrests > 10)
	{
		echoPrint << "You are not that interesting."
			<< "You can only have 10 interests."
			<< "Reenter Number of Interests: ";
		cin >> numIntrests;
		outFile << numIntrests;
 	}

	cin.ignore();
	for (int i = 0; i < numIntrests; i++)
	{
		echoPrint << "Interest " << i + 1 << ": ";
		getline(cin, str);
		outFile << str;
		newMember.setInterests(str, i);
	}
	echoPrint << "\n";
	
	// find client's sex, then search for a member of the opposite sex that 
	//     has at least 3 of the same interests. then add the member to their sex's list
	if (memberSex == 'M')
	{
		femaleList->findMatch(newMember);
		maleList->newClient(newMember);
	}
	else if (memberSex == 'F')
	{
		maleList->findMatch(newMember);
		femaleList->newClient(newMember);
	}

	// if no match was found, print friendly message
	if (newMember.getMatch() == "")
	{
		echoPrint << "Congrats, you are unique! No one has your same interests.\n";
	}
	// if a match was found, find the match and print both parties' info
	else
	{
		Client match;
		str = newMember.getMatch();
		if (memberSex == 'M')
		{
			match = femaleList->findClient(str);
		}
		else if (memberSex == 'F')
		{
			match = maleList->findClient(str);
		}
		echoPrint << "\nYou have a match!\n";
		echoPrint << newMember.getClientInfo() << " - " << match.getClientInfo() << "\n";
	}

}

// unmatch a client from their match
void unmatch(ClientList *list)
{
	Client client;
	string str;
	echoPrint << "Enter your name: ";
	cin.ignore();
	getline(cin, str);
	outFile << str;
	client = list->findClient(str);
	list->unmatchClient(client);
}

// print all matched pairs
void printMatch(ClientList *maleList)
{
	echoPrint << maleList->printMatched();
}

// print all unmatched individuals
void printFree(ClientList *maleList, ClientList *femaleList)
{
	echoPrint << maleList->printFree();
	echoPrint << femaleList->printFree();
}