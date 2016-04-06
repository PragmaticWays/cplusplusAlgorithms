#ifndef DOCTOR_H
#define DOCTOR_H
#include <string>
using namespace std;

/*********************************
Class Doctor.h - This class represents a doctor used in Local Medical Clinic Scheduling Service 
	program. A doctor object will have a name, room number, and specialty code assigned to them. 

Author:		Adam Allard
Created:	06/20/15
Revisions:
**********************************/

class Doctor
{
private:
	string name;
	int roomNum;
	string code;
public:
	Doctor();
	~Doctor();

	void setName(string);
	void setRoomNum(int);
	void setCode(string);

	string getName() const;
	int getRoomNum() const;
	string getCode() const;
};
#endif

