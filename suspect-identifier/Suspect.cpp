#include "Suspect.h"

/************************************
Suspect.cpp - This class is a simple class to hold a person's
name and a linked list (see LinkedList.h)

Author:		Adam Allard
Created:	07/10/15
*************************************/

Suspect::Suspect()
	{ name = ""; }


Suspect::Suspect(string n)
	{ name = n; }


Suspect::~Suspect()
{
}


void Suspect::setName(string n)
	{ name = n; }


string Suspect::getName() const
	{ return name; }

// used to transform a pointer object into an object
void Suspect::copy(Suspect *ptr)
{
	setName(ptr->getName());
	attributes = ptr->attributes;
}