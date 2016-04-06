#ifndef PQ_SORTEDLINKED_H
#define PQ_SORTEDLINKED_H
#include <iostream>

/**************************************
PQ_SortedLinked.h - This class is a linked list priority queue to hold
						integers from smallest to largest value. 

Author:		Adam Allard
Created:	07/16/15
***************************************/
struct Node;

class PQ_SortedLinked
{
private:
	Node *front;
	int elementsAccessed;

public:
	PQ_SortedLinked();
	~PQ_SortedLinked();

	bool isEmpty() const;
	bool isFull() const;
	void makeEmpty();

	int getElementsAccessed();

	void enqueue(int);
	void dequeue(int&);
};
#endif

