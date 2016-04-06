#include "Suspect.h"
#include "SuspectTree.h"
#include "Tee.h"
#include "TeeIn.h"
#include <fstream>
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

/********************************************
Suspect Identifier - This program is for a police department
	that has a collected database of criminals stored in the file
	"criminals.mf" - this program helps to pick out the suspects for 
	a given case.

Author:		Adam Allard
Created:	07/10/15
*********************************************/

// echo print to screen and file
ofstream printLog("Criminal.trn");
Tee coutEcho(std::cout, printLog);

SuspectTree criminals;
SuspectTree currentCriminals;
string code;

void readCriminalList();
string menu();
string inquiryMenu();
void inquiryMenuHelper();
void add();
void inquiry();
void tip();
void check();
void print();
void cinEcho(string&);
void appendNewAdd(Suspect);
bool iequals(const string&, const string&);

int main()
{
	readCriminalList();

	string menuSelection;
	do
	{
		menuSelection = menu();

		if (menuSelection == "ADD" || menuSelection == "add" || menuSelection == "Add")
			add();
		else if (menuSelection == "INQUIRY" || menuSelection == "inquiry" || menuSelection == "Inquiry")
			inquiry();
		else if (menuSelection == "QUIT" || menuSelection == "quit" || menuSelection == "Quit")
			coutEcho << "\n";
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (12));
			coutEcho << "\nInvalid menu option. Please try again.\n\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (7));
		}

	} while (menuSelection != "QUIT" && menuSelection != "quit");

	system("pause");
	return 0;
}

// READ CRIMINAL LIST
// READS IN THE CURRENT CRIMINAL LIST - ADDS ALL CRIMINALS TO SUSPECT LIST
void readCriminalList()
{
	string str;
	fstream criminalList;
	criminalList.open("criminals.mf", std::ofstream::in);

	// CRIMINAL LIST IS IN THE FOLLOWING FORMAT:
	//	NAME, TIP, TIP, TIP, ..., #,

	if (criminalList)
	{
		do
		{
			Suspect *newCriminal = new Suspect();

			getline(criminalList, str, ',');
			newCriminal->setName(str);
			getline(criminalList, str, ' ');
			getline(criminalList, str, ',');

			while (str != "#")
			{
				newCriminal->attributes.appendNode(str);
				getline(criminalList, str, ' ');
				getline(criminalList, str, ',');
			}
			newCriminal->attributes.appendNode(str);

			Suspect addPerson;
			addPerson.copy(newCriminal);
			criminals.putItem(addPerson);
			getline(criminalList, str, '\n');

		} while (!criminalList.eof());
	}
	criminalList.close();
}

// MAIN MENU - CALLED -AT BEGINNING OF PROGRAM
//					  -AFTER A NEW CRIMINAL IS ADDED
//					  -AFTER AN INQUIRY IS FINISHED
string menu()
{
	string selection;
	coutEcho << "**************************************************\n";
	coutEcho << "Menu - Please choose one of the following commands\n";
	coutEcho << "\tADD\n\tINQUIRY\n\tQUIT\n";
	coutEcho << "Type in your command: ";
	cinEcho(selection);
	
	return selection;
}

// INQUIRY MENU - WILL CONTINUE TO CALL UNTIL INQUIRY IS SOLVED (ONLY ONE SUSPECT LEFT)
string inquiryMenu()
{
	string selection;
	coutEcho << "\n*** " << code << " ***\n";
	coutEcho << "\tTIP\n\tCHECK\n\tPRINT\n";
	coutEcho << "Type in your command: ";
	cinEcho(selection);

	return selection;
}

// ADDS NEW CRIMINAL TO CRIMINAL LIST AND FORMATTED TO FILE CORRECTLY 
void add()
{
	// create new suspect
	Suspect *person = new Suspect();
	string str;

	// get suspects name
	coutEcho << "\nWhat is the suspect's name: ";
	cinEcho(str);
	person->setName(str);

	// get suspects attributes 
	coutEcho << "\nEnter " << str << "'s attributes. Enter 0 when finished.\n";
	do
	{
		coutEcho << "- ";
		cinEcho(str);
		if (str != "0")
			person->attributes.appendNode(str);
		
	} while (str != "0");

	// add suspect to list
	Suspect addPerson;
	addPerson.copy(person);
	criminals.putItem(addPerson);
	appendNewAdd(addPerson);

	coutEcho << "\n";
}

// INITIAL INQUIRY CALL - CREATES NEW INQUIRY
void inquiry()
{
	coutEcho << "\n*** New Inquiry ***\n";
	coutEcho << "\nType new inquiry code name: ";
	cinEcho(code);

	currentCriminals = criminals;

	inquiryMenuHelper();
}

// INQUIRY HELPER FUNCTION KEEPS GETTING CALLED UNTIL INQUIRY IS SOLVED
void inquiryMenuHelper()
{
	string str = inquiryMenu();

	if (str == "TIP" || str == "tip" || str == "Tip")
		tip();
	else if (str == "CHECK" || str == "check" || str == "Check")
		check();
	else if (str == "PRINT" || str == "print" || str == "Print")
		print();
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (12));
		coutEcho << "\nInvalid menu option. Try again.\n\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (7));
		inquiryMenuHelper();
	}
}

// TIP PROMPTS USER TO ENTER AN ATTRIBUTE - ATTRIBUTE IS CHECKED WITH
//		ALL ATTRIBUTES IN ALL SUSPECTS TO ELIMINATE SUSPECTS WHO DO NOT MATCH
void tip()
{
	Suspect checkPerson;

	// get tip info
	string tip, suspectTip = "";
	coutEcho << "\nEnter the tip info: ";
	cinEcho(tip);

	currentCriminals.fillStack();

	// get first person in stack
	checkPerson = currentCriminals.getNextItem();
	
	// while next person is not "null"
	bool match = false;
	while (checkPerson.getName() != "")
	{
		// while there is no match and not at the end of the attribute list
		while (!match && suspectTip != "#")
		{
			suspectTip = checkPerson.attributes.getNextItem();
			if (iequals(suspectTip, tip))
				match = true;
		}
		if (!match)
			currentCriminals.deleteItem(checkPerson);

		// check next person, reset suspectTip and match
		checkPerson = currentCriminals.getNextItem();
		suspectTip = "";
		match = false;
	}
	if (currentCriminals.getLength() > 1)
		inquiryMenuHelper();
	else if (currentCriminals.getLength() == 1)
	{
		currentCriminals.fillStack();
		coutEcho << code << " Case has been solved.\n";
		coutEcho << "The only suspect left is " << currentCriminals.getNextItem().getName(); 
		coutEcho << "\nBook 'Em Danno\n\n";
	}
	else
	{
		coutEcho << "There are no suspects that match all given tips.\n\n";
	}
}

// CHECK USES A BINARY SEARCH FUNCTION TO SEE IF A CERTAIN CRIMINAL IS STILL A SUSPECT ON THIS INQUIRY
void check()
{
	string str;
	bool found = false;
	coutEcho << "\nEnter name: ";
	cinEcho(str);


	currentCriminals.getItem(str, found);

	coutEcho << "\n";
	if (!found)
		coutEcho << str << " is not a suspect for this case.\n";
	else
		coutEcho << str << " is still a suspect.\n";

	inquiryMenuHelper();
}

// PRINTS ALL CURRENT SUSPECTS FOR THIS INQUIRY
void print()
{
	Suspect person;
	currentCriminals.fillStack();
	person = currentCriminals.getNextItem();

	coutEcho << "\n" << code << " Current Suspects: \n";
	while (person.getName() != "")
	{
		coutEcho << "\t" << person.getName() << "\n";
		person = currentCriminals.getNextItem();
	}
	coutEcho << "\n";

	inquiryMenuHelper();
}

// USED IN PLACE OF ALL CIN CALLS TO ENABLE ECHO PRINTING TO PRINT LOG
void cinEcho(string &input)
{
	getline(cin, input);
	printLog << input;
}

// USED TO ADD NEW SUSPECT TO CLIENT LIST WITH PROPER FORMATTING
void appendNewAdd(Suspect newPerson)
{
	fstream criminalList;
	string str;

	criminalList.open("criminals.mf", std::fstream::app);

	criminalList << "\n";
	criminalList << newPerson.getName();
	criminalList << ", ";

	str = newPerson.attributes.getNextItem();

	while (str != "#")
	{
		criminalList << str;
		criminalList << ", ";
		str = newPerson.attributes.getNextItem();
	}
	criminalList << str;
	criminalList << ", ";

	criminalList.close();
}

// USED TO COMPARE STRINGS CASE INSENSITIVE
// source: http://stackoverflow.com/questions/11635/case-insensitive-string-comparison-in-c
bool iequals(const string& a, const string& b)
{
	unsigned int sz = a.size();
	if (b.size() != sz)
		return false;
	for (unsigned int i = 0; i < sz; ++i)
		if (tolower(a[i]) != tolower(b[i]))
			return false;
	return true;
}