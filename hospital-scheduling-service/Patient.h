#ifndef	PATIENT_H
#define PATIENT_H
#include <string>
using namespace std;
#include "Doctor.h"

/*********************************
Class Patient.h - This class represents a patient used in Local Medical Clinic Scheduling Service
	program, a patient will have a name, age, specialty code, and assigned doctor (see Doctor.h)

Author:		Adam Allard
Created:	06/20/15
Revisions:
**********************************/

class Patient
{
private:
	string name;
	int age;
	string code;
	Doctor doc;
public:
	Patient();
	~Patient();

	void setName(string);
	void setAge(int);
	void setCode(string);
	void setDoc(Doctor);

	string getName() const;
	int getAge() const;
	string getCode() const;
	Doctor getDoc() const;
};
#endif

