#ifndef PQ_MINHEAP_H
#define PQ_MINHEAP_H
#include "MinHeap.h"
#include <iostream>

/**********************************
PQ_MinHeap.h - This class is a minimum heap priority queue used to hold 
				integers. The root integer is the smallest int, with every child 
				being larger than the parent. 

Author:		Adam Allard
Created:	07/16/15
**********************************/

class PQ_MinHeap
{
private:
	int length;
	HeapType items;
	int maxItems;

public:
	PQ_MinHeap(int);
	~PQ_MinHeap();

	bool isEmpty() const;
	bool isFull() const;
	void makeEmpty();

	void enqueue(int);
	void dequeue(int&);

	int getElementsAccessed();
};

PQ_MinHeap::PQ_MinHeap(int size)
{
	maxItems = size;
	items.elements = new int[size];
	length = 0;
}

PQ_MinHeap::~PQ_MinHeap()
{
	delete[] items.elements;
}

bool PQ_MinHeap::isEmpty() const
{
	return length == 0;
}

bool PQ_MinHeap::isFull() const
{
	return length == maxItems;
}

void PQ_MinHeap::makeEmpty()
{
	length = 0;
}

void PQ_MinHeap::enqueue(int newItem)
{
	if (length == maxItems)
		std::cout << "Error: HEAP is maxed out.\n";
	else
	{
		length++;
		items.elements[length - 1] = newItem;
		items.reheapUp(0, length - 1);
	}
}

void PQ_MinHeap::dequeue(int &item)
{
	if (length == 0)
		std::cout << "Error: HEAP is empty.\n";
	else
	{
		item = items.elements[0];
		items.elements[0] = items.elements[length - 1];
		length--;
		items.reheapDown(0, length - 1);
	}
}

int PQ_MinHeap::getElementsAccessed()
{
	return items.elementsAccessed;
}

#endif

