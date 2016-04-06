#include "SuspectTree.h"

/************************************
SuspectTree.cpp - This class is a binary search tree class
used to hold Suspect objects (see Suspects.h). It also
holds a stack (see Stack.h) which is used for retrieving
particular suspects.

Author:		Adam Allard
Created:	07/10/15
*************************************/

SuspectTree::SuspectTree()
{
	root = NULL;
}

SuspectTree::~SuspectTree()
{
	destroy(root);
}

void SuspectTree::destroy(TreeNode*& tree)
{
	if (tree != NULL)
	{
		destroy(tree->left);
		destroy(tree->right);
		delete tree;
	}
}

SuspectTree::SuspectTree(const SuspectTree &original)
{
	copyTree(root, original.root);
}

void SuspectTree::operator=(const SuspectTree& original)
{
	if (&original == this)
		return;
	destroy(root);
	copyTree(root, original.root);
}

void SuspectTree::copyTree(TreeNode*& copy, const TreeNode* original)
{
	if (original == NULL)
		copy = NULL;
	else
	{
		copy = new TreeNode;
		copy->info = original->info;
		copyTree(copy->left, original->left);
		copyTree(copy->right, original->right);
	}
}

bool SuspectTree::isEmpty() const
{
	return root == NULL;
}

bool SuspectTree::isFull() const
{
	TreeNode* location;
	try
	{
		location = new TreeNode;
		delete location;
		return false;
	}
	catch (std::bad_alloc exception)
	{
		return true;
	}
}

void SuspectTree::putItem(Suspect person)
{
	insert(root, person);
}

void SuspectTree::insert(TreeNode*& tree, Suspect person)
{
	if (tree == NULL)
	{
		tree = new TreeNode;
		tree->right = NULL;
		tree->left = NULL;
		tree->info = person;
		position = root;
	}
	else if (person.getName() < tree->info.getName())
		insert(tree->left, person);
	else
		insert(tree->right, person);
}

void SuspectTree::deleteItem(Suspect person)
{
	makeDeletion(root, person);
}

void SuspectTree::makeDeletion(TreeNode*& tree, Suspect person)
{
	if (person.getName() < tree->info.getName())
		makeDeletion(tree->left, person);
	else if (person.getName() > tree->info.getName())
		makeDeletion(tree->right, person);
	else
		deleteNode(tree);
}

void SuspectTree::deleteNode(TreeNode*& tree)
{
	Suspect person;
	TreeNode* tempPtr;

	tempPtr = tree;
	if (tree->left == NULL)
	{
		tree = tree->right;
		delete tempPtr;
	}
	else if (tree->right == NULL)
	{
		tree = tree->left;
		delete tempPtr;
	}
	else
	{
		getPredecessor(tree->left, person);
		tree->info = person;
		makeDeletion(tree->left, person);
	}
}

void SuspectTree::getPredecessor(TreeNode* tree, Suspect& person)
{
	while (tree->right != NULL)
		tree = tree->right;
	person = tree->info;
}

int SuspectTree::getLength()
{
	return countNodes(root);
}

int SuspectTree::countNodes(TreeNode* tree)
{
	if (tree == NULL)
		return 0;
	else
		return countNodes(tree->left) + countNodes(tree->right) + 1;
}

Suspect SuspectTree::getItem(Suspect person, bool& found)
{
	retrieve(root, person, found);
	return person;
}

void SuspectTree::retrieve(TreeNode* tree, Suspect &person, bool &found)
{
	string currentName;
	string personName = person.getName();
	if (tree != NULL)
		currentName = tree->info.getName();
	else
		currentName = "";

	bool same = true;


	unsigned int size = personName.size();
	if (size != currentName.size())
		same = false;
	else
	{
		for (unsigned int i = 0; i < size; ++i)
		{
			if (tolower(personName[i]) != tolower(currentName[i]))
			{
				same = false;
			}
		}
		if (same)
		{
			person = tree->info;
			found = true;
		}
	}

	if (!found)
	{
		if (tree == NULL)
			found = false;
		else if (personName < currentName)
			retrieve(tree->left, person, found);
		else if (personName > currentName)
			retrieve(tree->right, person, found);
	}
}

Suspect SuspectTree::getNextItem()
{
	Suspect rtn;
	suspectStack.get(rtn);

	return rtn;
}

void SuspectTree::fillStack()
{
	fillStackHelper(root);
}

void SuspectTree::fillStackHelper(TreeNode* current)
{
	if (current != NULL)
	{
		fillStackHelper(current->left);
		suspectStack.push(current->info);
		fillStackHelper(current->right);
	}
}

void SuspectTree::deleteSuspect()
{
	Suspect s;
	suspectStack.pop(s);
}