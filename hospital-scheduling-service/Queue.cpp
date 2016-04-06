#include "Queue.h"

/*********************************
Class Queue.cpp - A queue used in Local Medical Clinic Scheduling Service
	program to hold the lists of patients for a specific room. 

Author:		Adam Allard
Created:	06/20/15
Revisions:
**********************************/

struct Node
{
	Patient patient;
	Node *next;
};

Queue::Queue(void)
{
	forward = NULL;
	aft = NULL;
	length = 0;
}

void Queue::makeEmpty()
{
	Node* temp;

	while (forward != NULL)
	{
		temp = forward;
		forward = forward->next;
		delete temp;
	}

	aft = NULL;
}

Queue::~Queue(void)
{
	makeEmpty();
}

bool Queue::isFull() const
{
	Node* nodePtr;
	try{
		nodePtr = new Node;
		delete nodePtr;
		return false;
	}
	catch (std::bad_alloc exception)
	{
		return true;
	}
}

bool Queue::isEmpty() const
{
	return (forward == NULL);
}

void Queue::enqueue(Patient pat)
{
	if (isFull())
		throw FullQueue();
	else
	{
		Node *nodePtr;
		nodePtr = new Node;
		nodePtr->patient = pat;
		nodePtr->next = NULL;

		if (aft == NULL)
			forward = nodePtr;
		else
			aft->next = nodePtr;

		aft = nodePtr;
		length++;
	}
}

void Queue::dequeue(Patient &pat)
{
	if (isEmpty())
		throw EmptyQueue();
	else
	{
		Node *temp;
		temp = forward;
		pat = forward->patient;

		if (forward == NULL)
			aft = NULL;
		
		delete temp;
		length--;
	}
}

Patient Queue::getForward() const
{
	if (isEmpty())
		throw EmptyQueue();
	else
		return forward->patient;
}

string Queue::getForwardName() const
{
	if (isEmpty())
		throw EmptyQueue();
	else
	{
		string name = forward->patient.getName();
		return name;
	}
}

int Queue::getLength() const
	{ return length; }
