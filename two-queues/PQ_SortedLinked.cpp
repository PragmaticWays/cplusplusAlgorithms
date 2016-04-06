#include "PQ_SortedLinked.h"

/**************************************
PQ_SortedLinked.h - This class is a linked list priority queue to hold
integers from smallest to largest value.

Author:		Adam Allard
Created:	07/16/15
***************************************/

struct Node
{
	int num;
	Node *next;
};

PQ_SortedLinked::PQ_SortedLinked()
{
	front = NULL;
	elementsAccessed = 0;
}

PQ_SortedLinked::~PQ_SortedLinked()
{
	makeEmpty();
}

bool PQ_SortedLinked::isEmpty() const
{
	return (front == NULL);
}

bool PQ_SortedLinked::isFull() const
{
	Node *location;
	try
	{
		location = new Node;
		delete location;
		return false;
	}
	catch (std::bad_alloc exception)
	{
		return true;
	}
}

void PQ_SortedLinked::makeEmpty()
{
	
}

void PQ_SortedLinked::enqueue(int item)
{
	if (isFull())
		std::cout << "Error: LinkedList is full.\n";
	else
	{
		Node *newNode = new Node;
		newNode->num = item;
		newNode->next = NULL;

		Node *previous = NULL;
		Node *temp = NULL;
		Node *location = front;
		bool moreToSearch = true;

		// if list is empty, put new node at beginning.
		if (front == NULL)
			front = newNode;
		else
		{
			while (moreToSearch)
			{
				// if the item is less than the current position, put item in 
				// current position spot, and then point to old position
				if (item < location->num)
				{
					temp = previous->next;					// place current position in temp
					previous->next = newNode;				// update current position to new item
					newNode->next = temp;					// put old position back behind new position
					moreToSearch = (location == NULL);
				}
				// otherwise move to the next position to check until there are no more positions
				else
				{
					moreToSearch = true;
					previous = location;

					if (location->next != NULL)
					{
						location = location->next;
						elementsAccessed++;
					}
					else
					{
						moreToSearch = false;
					}
				}
			}
			// update current position to new item - only used when item is being added to end of list
			previous->next = newNode;
		}
	}
}

// remove item from front of list
void PQ_SortedLinked::dequeue(int &item)
{
	if (isEmpty())
		std::cout << "Error: LinkedList is empty.\n";
	else
	{
		Node *temp;

		temp = front;
		item = front->num;
		front = front->next;

		delete temp;

		elementsAccessed++;
	}
}

int PQ_SortedLinked::getElementsAccessed()
{
	return elementsAccessed;
}