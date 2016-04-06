#ifndef ROOM_H
#define ROOM_H
#include "Queue.h"

/*********************************
Class Room.h - This class represents a waiting room used in Local Medical Clinic Scheduling Service
	program. Each room will have a room number, a status to indicate if the room is free or not, waiting list 
	queue (see Queue.h), and an associated doctor (see Doctor.h)

Author:		Adam Allard
Created:	06/20/15
Revisions:
**********************************/

class Room
{
private:
	int roomNum;
	bool roomStatus; // false = free ; true = taken
	
public:
	Queue waitingList;
	Doctor doc;

	Room();
	~Room();

	void setRoomNum(int r);
	void setRoomTaken();
	void setRoomFree();

	int getRoomNum();
	bool getRoomStatus() const;
}; 
#endif