#pragma once
#ifndef SUSPECT_H
#define SUSPECT_H
#include "LinkedList.h"
#include <string>
using namespace std;

/************************************
Suspect.h - This class is a simple class to hold a person's
	name and a linked list (see LinkedList.h) 

Author:		Adam Allard
Created:	07/10/15
*************************************/

class Suspect
{
private:
	string name;

public:
	LinkedList<string> attributes;

	Suspect();
	Suspect(string);
	~Suspect();

	void setName(string);
	string getName() const;

	void copy(Suspect*);
};
#endif