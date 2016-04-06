/**************************************
MinHeap.h - This struct is used in PQ_MinHeap class to aid the class
				with the proper reheaping functions and swapping elements.
				This struct makes sure the root node is the smallest value, while following
				the size and shape property. 

Author:		Adam Allard
Created:	07/16/15
***************************************/
void swap(int &one, int &two);

struct HeapType
{
	void reheapDown(int root, int bottom);
	void reheapUp(int root, int bottom);
	int * elements;
	int numElements;
	int elementsAccessed = 0;
};

void swap(int &one, int &two)
{
	int temp;
	temp = one;
	one = two;
	two = temp;
}

void HeapType::reheapDown(int root, int bottom)
{
	int minChild;
	int rightChild;
	int leftChild;

	leftChild = root * 2 + 1;
	rightChild = root * 2 + 2;

	if (leftChild <= bottom)
	{
		if (leftChild == bottom)
			minChild = leftChild;
		else
		{
			if (elements[leftChild] >= elements[rightChild])
				minChild = rightChild;
			else
				minChild = leftChild;
		}

		if (elements[root] > elements[minChild])
		{
			swap(elements[root], elements[minChild]);
			elementsAccessed++;
			reheapDown(minChild, bottom);
		}
	}
}

void HeapType::reheapUp(int root, int bottom)
{
	int parent;

	if (bottom > root)
	{
		parent = (bottom - 1) / 2;
		if (elements[parent] > elements[bottom])
		{
			swap(elements[parent], elements[bottom]);
			elementsAccessed++;
			reheapUp(root, parent);
		}
	}
}

