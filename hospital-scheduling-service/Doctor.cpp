#include "Doctor.h"

/*********************************
Class Doctor.cpp - This class represents a doctor used in Local Medical Clinic Scheduling Service 
	program. A doctor object will have a name, room number, and specialty code assigned to them. 

Author:		Adam Allard
Created:	06/20/15
Revisions:
**********************************/

Doctor::Doctor()
{
	name = "";
	roomNum = 0;
	code = "";
}

Doctor::~Doctor()
{}

	// setters
void Doctor::setName(string n)
	{ name = n; }

void Doctor::setRoomNum(int r)
	{ roomNum = r; }

void Doctor::setCode(string c)
	{ code = c; }

	// getters
string Doctor::getName() const
	{ return name; }

int Doctor::getRoomNum() const
	{ return roomNum; }

string Doctor::getCode() const
	{ return code; }
