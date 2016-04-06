#ifndef QUEUE_H
#define QUEUE_H
#include "Patient.h"

/*********************************
Class Queue.h - A queue used in Local Medical Clinic Scheduling Service
	program to hold the lists of patients for a specific room. 

Author:		Adam Allard
Created:	06/20/15
Revisions:
**********************************/

class FullQueue
{};

class EmptyQueue
{};

struct Node;

class Queue
{
private:
	Node *forward;
	Node *aft;
	int length;

public:
	Queue();
	~Queue();
	void makeEmpty();
	void enqueue(Patient);
	void dequeue(Patient&);
	bool isEmpty() const;
	bool isFull() const;
	int getLength() const;
	Patient getForward() const;
	string getForwardName() const;
};
#endif
