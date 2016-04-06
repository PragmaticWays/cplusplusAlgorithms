#include "Room.h"

/*********************************
Class Room.cpp - This class represents a waiting room used in Local Medical Clinic Scheduling Service
program. Each room will have a room number, a status to indicate if the room is free or not, waiting list
queue (see Queue.h), and an associated doctor (see Doctor.h)

Author:		Adam Allard
Created:	06/20/15
Revisions:
**********************************/

Room::Room()
{
	roomNum = 0;
	roomStatus = false;
}
Room::~Room()
{

}

void Room::setRoomNum(int r)
{
	roomNum = r;
}
void Room::setRoomTaken()
{
	roomStatus = true;
}
void Room::setRoomFree()
{
	roomStatus = false;
}


int Room::getRoomNum()
{
	return roomNum;
}
bool Room::getRoomStatus() const
{
	return roomStatus;
}