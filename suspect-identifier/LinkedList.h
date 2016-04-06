/*****************************************
Class LinkedList.h

This is a linked list template class which can append, insert, and delete
elements from the list. It also has functions to display the list
and search for an element in this list.

Author: Adam Allard
Created: 04/15/15
Revisions: 04/15/15 - Initial
		   04/16/15 - Added searchList function
		   07/10/15 - Commented out destructor due to bug in program
					- Added getNextItem()
******************************************/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
using namespace std;

template <class T>
class LinkedList
{
private:

	struct ListNode
	{
		T value;
		struct ListNode *next;
	};

	ListNode *head;
	ListNode *currentPos;

public:
	LinkedList();
	// ~LinkedList();   // destructor crashed the program - have no clue why, any suggestions?

	void appendNode(T);
	void insertNode(T);
	void deleteNode(T);
	void displayList() const;

	int searchList(T) const;

	T getNextItem();

};

/********* constructor ***********/
template <class T>
LinkedList<T>::LinkedList()
{
	head = nullptr;
	currentPos = head;
}

/********* destructor ***********/

/* 

template <class T>
LinkedList<T>::~LinkedList()
{
	ListNode *nodePtr;
	ListNode *nextNode;
	nodePtr = head;

	while (nodePtr != nullptr)
	{
		nextNode = nodePtr->next;
		delete nodePtr;
		nodePtr = nextNode;
	}
}

*/

/********* append ***********/
template <class T>
void LinkedList<T>::appendNode(T num)
{
	ListNode *newNode;
	ListNode *nodePtr;

	newNode = new ListNode;
	newNode->value = num;
	newNode->next = nullptr;

	if (!head)
		head = newNode;
	else
	{
		nodePtr = head;

		while (nodePtr->next)
			nodePtr = nodePtr->next;

		nodePtr->next = newNode;
	}
}

/********* insert ***********/
template <class T>
void LinkedList<T>::insertNode(T num)
{
	ListNode *newNode;
	ListNode *nodePtr;
	ListNode *previousNode = nullptr;

	newNode = new ListNode;
	newNode->value = num;

	if (!head)
	{
		head = newNode;
		newNode->next = nullptr;
	}
	else
	{
		nodePtr = head;
		previousNode = nullptr;

		while (nodePtr != nullptr && nodePtr->value < num)
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		if (previousNode == nullptr)
		{
			head = newNode;
			newNode->next = nodePtr;
		}
		else
		{
			previousNode->next = newNode;
			newNode->next = nodePtr;
		}
	}
}

/********* delete ***********/
template <class T>
void LinkedList<T>::deleteNode(T num)
{
	ListNode *nodePtr;
	ListNode *previousNode = nullptr;

	if (!head)
		return;

	if (head->value == num)
	{
		nodePtr = head->next;
		delete head;
		head = nodePtr;
	}
	else
	{
		nodePtr = head;

		while (nodePtr != nullptr && nodePtr->value != num)
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		if (nodePtr)
		{
			previousNode->next = nodePtr->next;
			delete nodePtr;
		}
	}
}

/********* display ***********/
template <class T>
void LinkedList<T>::displayList() const
{
	ListNode *nodePtr;
	nodePtr = head;

	while (nodePtr)
	{
		cout << "nodePtr->value" << endl;
		nodePtr = nodePtr->next;
	}
	cout << endl;
}

/********* search ***********/
template <class T>
int LinkedList<T>::searchList(T num) const
{
	int index = 0;

	ListNode *nodePtr;
	nodePtr = head;

	while (nodePtr)
	{
		if (nodePtr->value == num)
			return index;
		else
		{
			nodePtr = nodePtr->next;
			index++;
		}
	}

	index = -1;
	return index;
}

template <class T>
T LinkedList<T>::getNextItem()
{
	string done = "#";

	if (currentPos == NULL)
		currentPos = head;
	else
		currentPos = currentPos->next;

	if (currentPos != NULL)
		return currentPos->value;
	else
		return done;
}
#endif