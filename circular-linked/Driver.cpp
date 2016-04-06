#include <iostream>
#include "UnsortedType.h"
using namespace std;

/*********************************
Circular Linked List Driver
    This program tests the circular linked list template class (UnsortedType.h)
    to ensure that the class works as it's intended to. 

Author:     Adam Allard
Created:    06/27/15
*********************************/

void displayList(UnsortedType<int> *, int);

int main()
{
    // CREATE NEW LIST WITH TYPE INT
	UnsortedType<int> *list = new UnsortedType<int>();

    // FILL LIST WITH INTS 1 THROUGH 9
	int item = 1;
	for (int i = 0; i < 9; i++)
	{
		list->InsertItem(item);
		item++;
	}

    // DISPLAY LIST TO PROVE ALL ITEMS WERE INSERTED
	displayList(list, item);

	// RESET LIST 
	list->ResetList();

	// DISPLAY LIST TO PROVE THE LIST WAS RESET
	displayList(list, item);

    // DELETE 2 FROM LIST
	list->DeleteItem(2);

	// DISPLAY LIST TO PROVE 2 WAS DELETED FROM LIST 
	displayList(list, item);

	// DELETE 5 FROM LIST
	list->DeleteItem(5);

	// DISPLAY LIST TO PROVE 5 WAS DELETED FROM LIST 
	displayList(list, item);

    // RESET LIST 
	list->ResetList();

	// DISPLAY LIST TO PROVE THE LIST WAS RESET
	displayList(list, item);

    // INSERT ANOTHER INT
	list->InsertItem(2);

    // DISPLAY LIST TO PROVE THAT 2 WAS ADDED TO LIST
	displayList(list, item);

	// RESET LIST 
	list->ResetList();

	// DISPLAY LIST TO PROVE THE LIST WAS RESET
	displayList(list, item);

	cout << endl;
	system("pause");
	return 0;
}

// DISPLAY LIST - ITERATES THROUGH LIST TO DISPLAY ALL ITEMS
void displayList(UnsortedType<int> *c, int i)
{
	for (int ind = 0; ind < c->GetLength(); ind++)
	{
		c->GetNextItem(i);
		cout << i;
	}
	cout << endl;
}