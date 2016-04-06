/*

Implementation file for the Linked Que Class.

*/

#include "LinkedQue.h"
#include <cstddef>
#include <new>

struct NodeType
{
	patient info;
	NodeType* next;
};

// Default constructor
LinkedQue::LinkedQue(void)
{
	front = NULL;
	rear = NULL;
	length = 0;
}

// Make the que empty by setting the front and rear to NULL.
void LinkedQue::MakeEmpty()
{
	NodeType* tempPtr;

	while (front != NULL)
	{
		tempPtr = front;
		front = front->next;
		delete tempPtr;
	}

	rear = NULL;
}

// Deconstructor.
LinkedQue::~LinkedQue(void)
{
	MakeEmpty();

}

// Returns a bool.  If the que is full, return true.
bool LinkedQue::IsFull() const
{
	NodeType* location;
	try{
		location = new NodeType;
		delete location;
		return false;
	}
	catch (std::bad_alloc exception)
	{
		return true;
	}
}

// Returns a bool.  If the que is empty, it returns true.
bool LinkedQue::IsEmpty() const
{
	return (front == NULL);
}

// Accepts a patient variable and adds it to the que.
void LinkedQue::Enqueue(patient newItem)
{
	if (IsFull())
		throw FullQueue();
	else
	{
		NodeType* newNode;

		newNode = new NodeType;
		newNode->info = newItem;
		newNode->next = NULL;
		if (rear == NULL)
		{
			front = newNode;
		}
		else
		{
			rear->next = newNode;
		}
		rear = newNode;
		length++; // Inc length.
	}

}

// Accepts a reference to a patient variable.  It will remove the
// front item from the que and set the reference to the next patient.
void LinkedQue::Dequeue(patient& item)
{
	if (IsEmpty())
	{
		throw EmptyQueue();
	}
	else
	{
		NodeType* tempPtr;

		tempPtr = front;
		item = front->info;
		front = front->next;
		if (front == NULL)
		{
			rear = NULL;
		}
		delete tempPtr;
		length--;
	}

}

// Returns the length of the que.
int LinkedQue::GetLength() const
{
	return length;
}