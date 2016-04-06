#ifndef UNSORTEDTYPE_H
#define UNSORTEDTYPE_H
#include <iostream>
using namespace std;

/*****************************************
Class UnsortedType.h
    This class is a template class of an unsorted
    circular linked list.

Author:     Adam Allard
Created:    06/27/15
******************************************/

template <class ItemType>
class UnsortedType
{
private:
	template <class ItemType>
	struct NodeType
	{
		ItemType info;
		NodeType* next;
	};

	NodeType<ItemType> *listData;
	NodeType<ItemType> *currentPos;
	int length;

public:
	UnsortedType();
	~UnsortedType();
	UnsortedType(const UnsortedType<ItemType>&);

	void operator=(UnsortedType<ItemType>);

	bool IsFull() const;
	int GetLength() const;
	void RetrieveItem(ItemType& item, bool& found);
    void InsertItem(ItemType item);
	void DeleteItem(ItemType item);
	void ResetList();
	void GetNextItem(ItemType&);
};


/******** IMPLEMENTATION **************/

// CONSTRUCTOR
template <class ItemType>
UnsortedType<ItemType>::UnsortedType()
{
	listData = NULL;
	currentPos = NULL;
	length = 0;
}

// DESTRUCTOR
template <class ItemType>
UnsortedType<ItemType>::~UnsortedType()
{
	NodeType<ItemType> *tempPtr;
	NodeType<ItemType> *delPtr;

	tempPtr = listData;
	for (int i = 0; i <= length - 1; i++)
	{
		delPtr = tempPtr;
		delete delPtr;
		tempPtr = tempPtr->next;
	}
	tempPtr = currentPos;
	for (int i = 0; i <= length - 1; i++)
	{
		delPtr = tempPtr;
		delete delPtr;
		tempPtr = tempPtr->next;
	}
	length = 0;
}

// COPY CONSTRUCTOR
template <class ItemType>
UnsortedType<ItemType>::UnsortedType(const UnsortedType<ItemType> &item)
{
	*this = item;
}

// OVERRIDDEN =OPERATOR
template <class ItemType>
void UnsortedType<ItemType>::operator=(UnsortedType<ItemType> item)
{
	listData = item.listData;
	length = item.length;
	currentPos = item.currentPos;
}

// IS FULL - CHECKS IF LIST IS FULL
template <class ItemType>
bool UnsortedType<ItemType>::IsFull() const
{
	NodeType<ItemType> *tempPtr = new NodeType < ItemType >;
	if (tempPtr == NULL)
		return true;
	else
	{
		delete tempPtr;
		return false;
	}
}

// GET LENGTH - RETURNS HOW MANY ITEMS IN LIST
template <class ItemType>
int UnsortedType<ItemType>::GetLength() const
{
	return length;
}

// RETRIEVE ITEM - RETURNS (THRU REFERENCE VAR PARAMETER) ITEM IN LIST IF FOUND
template <class ItemType>
void UnsortedType<ItemType>::RetrieveItem(ItemType &item, bool &found)
{
	NodeType<ItemType> *tempPtr;
	tempPtr = listData;

	for (int i = 1; i <= length; i++)
	{
		if (tempPtr->info == item)
		{
			found = true;
			return;
		}
		tempPtr = tempPtr->next;
	}
	found = false;
}

// INSERT ITEM - INSERTS ITEM INTO LIST IF ITEM IS NOT ALREADY THERE
template <class ItemType>
void UnsortedType<ItemType>::InsertItem(ItemType item)
{
	NodeType<ItemType> *tempPtr = new NodeType < ItemType >;
	NodeType<ItemType> *currentPtr;
	ItemType newItem = item;
	bool found;

	RetrieveItem(newItem, found);

	if (found)
		return;

	currentPtr = listData;
	tempPtr->info = item;

	if (listData == NULL)
	{
		listData = tempPtr;
		tempPtr->next = listData;
	}
	else
	{
		while (currentPtr->next != listData)
		{
			currentPtr = currentPtr->next;
		}
		currentPtr->next = tempPtr;
		tempPtr->next = listData;
	}
	currentPos = listData;
	length++;
}

// DELETE ITEM - DELETES ITEM FROM LIST IF ITEM IS THERE
template <class ItemType>
void UnsortedType<ItemType>::DeleteItem(ItemType item)
{
	NodeType<ItemType> *tempPtr;
	NodeType<ItemType> *currentPtr;
	NodeType<ItemType> *behindCurrent;
	bool found;

	if (length == 0)
	{
		cout << "List is empty." << endl;
		return;
	}

	RetrieveItem(item, found);

	if (!found)
	{
		cout << "That item is not in the list." << endl;
		return;
	}

	currentPtr = listData;
	behindCurrent = currentPtr;

	if (listData == currentPtr->next)
	{
		if (currentPtr->info == item)
		{
			listData = NULL;
			delete behindCurrent;
			return;
		}
	}

	for (int i = 0; i <= length - 1; i++)
	{
		if (currentPtr->next->info == item)
		{
			tempPtr = currentPtr->next;
			currentPtr->next = currentPtr->next->next;
			delete tempPtr;
		}
		else
			currentPtr = currentPtr->next;
	}

	length--;
}

// RESET LIST - INITIALIZES CURRENT POSITION FOR AN ITERATION THROUGH LIST
template <class ItemType>
void UnsortedType<ItemType>::ResetList()
{
	NodeType<ItemType> *tempPtr;

	tempPtr = listData;

	if (length <= 1)
		return;

	for (int i = 0; i < length - 1; i++)
	{
		tempPtr = tempPtr->next;
		currentPos = tempPtr;
	}
}

// GET NEXT ITEM - GETS NEXT ITEM IN LIST, MOVES CURRENT POSITION TO NEXT POSITION
template <class ItemType>
void UnsortedType<ItemType>::GetNextItem(ItemType& item)
{
	NodeType<ItemType> *tempPtr;
	tempPtr = currentPos;
	item = tempPtr->next->info;
	currentPos = currentPos->next;
}
#endif