#include "PegStack.h"
#include <iostream>
#include <Windows.h>
using namespace std;

/*************************************************
Towers of Hanoi Calculator
	   This program calculates the shortest amount of moves to complete
	the game Towers of Hanoi. This game has a base with three pegs and 
	discs of different diameters. The discs begin on one peg, with the 
	largest disk on the bottom and the other disks added on in order of 
	size. The idea is to move the discs from the peg they are on to 
	another peg by moving only one disc at a time and without ever putting 
	a larger disc on top of a smaller one. 

	   The pegs are implemented by a static stack class (see PegStack.h) to 
	hold the discs. 

Author:		Adam Allard
Created:	06/29/15
*************************************************/

void findMove(int, char, char, char);
void performMove(char, char);
void showPegs();
void showIntro();

// ENTER HERE HOW MANY DISCS YOU WISH TO PLAY WITH
int numDiscs = 5;

// CREATE 3 PEGS AS STACKS TO HOLD DISCS
PegStack first(numDiscs);
PegStack second(numDiscs);
PegStack third(numDiscs);

int main()
{
	// FILL FIRST PEG WITH DISCS
	for (int i = numDiscs; i > 0; i--)
		first.addDisc(i);

	// CREATE 3 INTS TO SIMULATE PEGS FOR RECURSIVE FUNCTION
	int one = 'A';
	int two = 'B';
	int tee = 'C';

	// DISPLAY INTRO - THEN CALCULATE QUICKEST WAY TO BEAT THE GAME
	showIntro();
	findMove(numDiscs, one, two, tee);

	// END PROGRAM - DISPLAY A FRIENDLY MESSAGE
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
	cout << "  GO PACK GO" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (2));
	cout << "**************" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (7));
	cout << "Press any key to cheer for Green Bay . . .";
	system("pause > nul");
	return 0;
}

// findMove IS A RECURSIVE FUNCTION THAT HOLDS THE LOGIC TO
//	FIND THE SHORTEST AMOUNT OF MOVES TO BEAT THE GAME
void findMove(int n, char a, char b, char c)
{
	if (n > 0)
	{
		findMove((n - 1), a, c, b);
		performMove(a, c);
		findMove((n - 1), b, a, c);
	}
}

// performMove IS CALLED FROM findMove AND IS RESPONSIBLE
//	FOR ACTUALLY MOVING A DISC FROM ONE PEG TO THE OTHER
void performMove(char source, char destination)
{
	int move;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
	cout << "Move " << source << " -> " << destination << endl;

	if (source == 'A')
		move = first.removeDisc();
	else if (source == 'B')
		move = second.removeDisc();
	else
		move = third.removeDisc();

	if (destination == 'A')
		first.addDisc(move);
	else if (destination == 'B')
		second.addDisc(move);
	else
		third.addDisc(move);

	showPegs();
}

// showPegs DISPLAYS THE 3 PEGS AND ALL, IF ANY, DISCS ON THE PEGS 
// IN ORDER - THE PEGS ARE DISPLAYED HORIZONTALLY
void showPegs()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (2));
	cout << " A|";
	first.displayPeg();
	cout << endl;
	cout << " B|";
	second.displayPeg();
	cout << endl;
	cout << " C|";
	third.displayPeg();
	cout << endl << "**************" << endl;
}

// showIntro IS AN OPENING MESSAGE TO THE PROGRAM AND GOES 
//	IMMEDIATELY INTO THE showPegs METHOD. 
void showIntro()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (2));
	cout << "********************************************" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14));
	cout << "       (Horizontal) Towers of Hanoi" << endl
		<< " This program calculates the shortest amount" << endl
		<< " of moves to complete the game. The pegs are" << endl
		<< " oriented in a horizontal view - A, B, and C" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (2));
	cout << "********************************************" << endl;
	showPegs();
}

