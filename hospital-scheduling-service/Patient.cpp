#include "Patient.h"

/*********************************
Class Patient.cpp - This class represents a patient used in Local Medical Clinic Scheduling Service
	program, a patient will have a name, age, specialty code, and assigned doctor (see Doctor.h)

Author:		Adam Allard
Created:	06/20/15
Revisions:
**********************************/

Patient::Patient()
{
	name = "";
	age = 0;
	code = "";
}

Patient::~Patient()
{}

	// setters
void Patient::setName(string n)
	{ name = n; }

void Patient::setAge(int a)
	{ age = a; }

void Patient::setCode(string c)
	{ code = c; }

void Patient::setDoc(Doctor d)
	{ doc = d; }

	// getters
string Patient::getName() const
	{ return name; }

int Patient::getAge() const
	{ return age; }

string Patient::getCode() const
	{ return code; }

Doctor Patient::getDoc() const
	{ return doc; }
