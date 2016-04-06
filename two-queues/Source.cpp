#include "PQ_MinHeap.h"
#include "PQ_SortedLinked.h"
#include <iostream>
#include <cstdlib>
using namespace std;

/******************************************
Two Queues
	This program compares two implementations of a priority queue - 
	one is a minimum heap, and the other is a linked list. The elements in 
	both implementations are ordered from smallest to largest. The program
	compares and demostrates how much more effective a heap priority queue can be
	over a linked list queue. 

Author:		Adam Allard
Created:	07/16/15
******************************************/

// function displays the number passed to it
void displayDQ(int);


int main()
{
	// create and fill array of 50 random ints
	int dataset[50];

	for (int i = 0; i < 50; i++)
		dataset[i] = rand();

	// display origional order of array
	cout << "ORIGINAL ORDER:" << endl;
	for (int i = 0; i < 50; i++)
		cout << dataset[i] << endl;
	cout << endl;

	int number;

	// create linked list priority queue - filling list with dataset array elements
	PQ_SortedLinked list;

	cout << "ADDING DATASET TO LINKED LIST " << endl << endl;

	for (int i = 0; i < 50; i++)
		list.enqueue(dataset[i]);

	// dequeue all 50 numbers. this will display the first 5 numbers and the last number only to save space and 
	// for better readability
	list.dequeue(number);
	displayDQ(number);
	list.dequeue(number);
	displayDQ(number);
	list.dequeue(number);
	displayDQ(number);
	list.dequeue(number);
	displayDQ(number);
	list.dequeue(number);
	displayDQ(number);
	cout << "." << endl << "." << endl << "." << endl;
	for (int i = 0; i < 45; i++)
		list.dequeue(number);
	displayDQ(number);

	cout << endl;

	cout << "NOW ADDING DATASET TO MINIMUM HEAP PRIORITY QUEUE" << endl << endl;

	// create minimum heap priority queue - filling list with dataset array elements

	PQ_MinHeap heap(50);

	for (int i = 0; i < 50; i++)
		heap.enqueue(dataset[i]);

	// dequeue all 50 numbers. this will display the first 5 numbers and the last number only to save space and 
	// for better readability
	heap.dequeue(number);
	displayDQ(number);
	heap.dequeue(number);
	displayDQ(number);
	heap.dequeue(number);
	displayDQ(number);
	heap.dequeue(number);
	displayDQ(number);
	heap.dequeue(number);
	displayDQ(number);
	cout << "." << endl << "." << endl << "." << endl;
	for (int i = 0; i < 45; i++)
		heap.dequeue(number);
	displayDQ(number);

	// shows how many elements needed to be accessed per priority queue implementation
	cout << endl;
	cout << "LINKED LIST IMPLEMENTATION ACCESSED " << list.getElementsAccessed() << " ELEMENTS." << endl;
	cout << "MINIMUM HEAP IMPLEMENTATION ACCESSED " << heap.getElementsAccessed() << " ELEMENTS." << endl;

	// end program
	cout << endl;
	system("pause");
	return 0;
}

// this function displays the number that was dequeued (passed as parameter)
void displayDQ(int num)
{
	cout << num << " is dequeued." << endl;
}