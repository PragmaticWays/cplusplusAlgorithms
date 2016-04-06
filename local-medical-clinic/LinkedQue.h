/*

Linked Que Class

This class will be used to create a que that holds patient data.

*/

#include <string>
using namespace std;

class FullQueue
{};

class EmptyQueue
{};

// Creat a struct to hold patient data.  This will be the item to be stored in the que.
struct patient {
	string name;
	int specialty;
	int age;
	string emergencyDescription;
};

struct NodeType;

class LinkedQue
{
public:
	LinkedQue();
	~LinkedQue();
	void MakeEmpty();		// Make the que empty.
	void Enqueue(patient);	// Enque a patient.
	void Dequeue(patient&);	// Deque a patient.
	bool IsEmpty() const;	// Check to see if the que is empty.
	bool IsFull() const;	// Check to see if the que is full.
	int GetLength() const;	// Return the length of the que.
private:
	NodeType* front;		// A pointer to the front.
	NodeType* rear;		// A pointer to the back.
	int length;			// Hold the the size of the que.
};

