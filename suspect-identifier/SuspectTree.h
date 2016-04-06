#ifndef SUSPECTTREE
#define SUSPECTTREE
#include "Suspect.h"
#include "Stack.h"

/************************************
SuspectTree.h - This class is a binary search tree class 
	used to hold Suspect objects (see Suspects.h). It also
	holds a stack (see Stack.h) which is used for retrieving 
	particular suspects. 

Author:		Adam Allard
Created:	07/10/15
*************************************/

class SuspectTree
{
private:
	struct TreeNode
	{
		Suspect info;
		TreeNode *left;
		TreeNode *right;
	};
	TreeNode *root;
	TreeNode *position;

	Stack<Suspect> suspectStack;

	// helper functions
	void destroy(TreeNode*&);
	void copyTree(TreeNode*&, const TreeNode*);
	int countNodes(TreeNode*);
	void retrieve(TreeNode*, Suspect&, bool&);
	void insert(TreeNode*&, Suspect);
	void deleteNode(TreeNode*&);
	void makeDeletion(TreeNode*&, Suspect);
	void getPredecessor(TreeNode*, Suspect&);
	void fillStackHelper(TreeNode*);

public:
	SuspectTree();
	~SuspectTree();

	SuspectTree(const SuspectTree &);
	void operator=(const SuspectTree &);

	bool isEmpty() const;
	bool isFull() const;

	void putItem(Suspect);
	void deleteItem(Suspect);
	void makeEmpty();
	int getLength();
	Suspect getItem(Suspect, bool&);

	Suspect getNextItem();
	void fillStack();
	void deleteSuspect();
};
#endif