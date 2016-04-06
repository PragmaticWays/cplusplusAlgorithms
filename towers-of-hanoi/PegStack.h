#ifndef PEGSTACK_H
#define PEGSTACK_H

/*******************************
PegStack.h
	This class is a static stack class
	used to hold discs (integers) on a peg
	for the game Towers of Hanoi. 

	The standard push() and pop() methods
	are called addDisc and removeDisc, respectively.

	There is also displayPeg method to display
	all the discs in the peg. 

Author:		Adam Allard
Created:	06/29/15
*******************************/
class PegStack
{
private:
	int *stackArray;
	int stackSize;
	int discs;
public:
	PegStack(int);
	~PegStack();

	void addDisc(int); // push
	int removeDisc();  // pop

	bool isFull() const;
	bool isEmpty() const;

	void displayPeg() const;
};
#endif

