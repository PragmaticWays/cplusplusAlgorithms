#include "PegStack.h"
#include <iostream>
using namespace std;

/*******************************
PegStack.cpp
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

PegStack::PegStack(int size)
{
	stackArray = new int[size];
	stackSize = size;
	discs = -1;
}

PegStack::~PegStack()
{
	delete[] stackArray;
}

// PUSH
void PegStack::addDisc(int num)
{
	if (isFull())
		cout << "This peg cannot hold any more discs." << endl;
	else
	{
		discs++;
		stackArray[discs] = num;
	}
}

// POP
int PegStack::removeDisc()
{
	int retrn;
	if (isEmpty())
		cout << "This peg has no discs." << endl;
	else
	{
		retrn = stackArray[discs];
		discs--;
	}
	return retrn;
}

bool PegStack::isFull() const
{
	bool status;

	if (discs == stackSize - 1)
		status = true;
	else
		status = false;

	return status;
}

bool PegStack::isEmpty() const
{
	bool status;

	if (discs == -1)
		status = true;
	else
		status = false;

	return status;
}

void PegStack::displayPeg() const
{
	for (int i = 0; i < discs + 1; i++)
		cout << " " << stackArray[i];
}