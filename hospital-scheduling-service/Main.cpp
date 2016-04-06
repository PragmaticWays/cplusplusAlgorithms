#include "Doctor.h"
#include "Patient.h"
#include "Queue.h"
#include "Room.h"
#include "Tee.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// used to echo print to screen and file
ofstream outFile("Trans.txt");
Tee echoPrint(std::cout, outFile);

/*********************************
Local Medical Clinic Scheduling Service - This program schedules doctors and patients 
	to check in and out. 

Author:		Adam Allard
Created:	06/20/15
Revisions:	
**********************************/

int main()
{
	string name;
	int room;
	string code;
	int age;

	Room rooms[100];
	for (int i = 0; i < 100; i++)
	{
		rooms[i].setRoomNum(i + 100);
	}

	string codes[12] = { "PED", "GEN", "INT", "CAR", "SUR", "OBS",
						 "PSY", "NEU", "ORT", "DET", "OPT", "ENT" };

	Patient newPat;
	Patient *patPtr;
	patPtr = &newPat;

	Doctor newDoc;
	Doctor *docPtr;
	docPtr = &newDoc;

	char shutDownOption; // used at end of do-while loop

	do
	{
		// prompt user for info
		char inputP;
		echoPrint << "Type D for Doctor or P for Patient: ";
		cin >> inputP;
		outFile << inputP;

		// check info
		while (toupper(inputP) != 'D' && toupper(inputP) != 'P')
		{
			echoPrint << "That is not a valid option.\n"
				<< "Type D for Doctor or P for Patient: ";
			cin >> inputP;
			outFile << inputP;
		}

		// prompt user for info
		char inputIO;
		echoPrint << "Type I for check-in or O for check-out: ";
		cin >> inputIO;
		outFile << inputIO;

		// check info
		while (toupper(inputIO) != 'I' && toupper(inputIO) != 'O')
		{
			echoPrint << "That is not a valid option.\n" 
				<< "Type I for check-in or O for check-out: ";
			cin >> inputIO;
			outFile << inputIO;
		}

		/************** doctor check in *******************/
		if (toupper(inputP) == 'D')
		{
			if (toupper(inputIO == 'I'))
			{

			// get doc's name
				Doctor *doc = new Doctor();
				cin.ignore();
				echoPrint << "\nEnter your name: ";
				getline(cin, name);
				outFile << name;
				doc->setName(name);

			// get doc's room
				echoPrint << "What is your preffered room (100 - 199) : ";
				cin >> room;
				outFile << room;
				while (room < 100 && room > 199)
				{
					echoPrint << "Invalid room number.\n"
						 << "What is your preffered room (100 - 199) : ";
					cin >> room;
					outFile << room;
				}

				// find room, check status, if free, set room to doc
				for (int i = 0; i < 100; i++) 
				{
					if (room == rooms[i].getRoomNum()) 
					{
						if (!rooms[i].getRoomStatus()) 
						{
							doc->setRoomNum(room);
							rooms[i].setRoomTaken();
							rooms[i].doc.setName(name);
							rooms[i].doc.setRoomNum(room);
						} 
					} 
				}

			// get docs specialist code
				bool found = false;
				do
				{
					echoPrint << "What is your specialist code: ";
					cin >> code;
					outFile << code;

					for (int i = 0; i < 12; i++)
					{
						if (code == codes[i])
						{
							found = true;
							doc->setCode(code);
						}
					}
					if (!found)
						echoPrint << "Invalid specialist code.\n";
				} while (!found);

				// if room is taken by another doctor
				if (rooms[room - 100].getRoomStatus() && rooms[room - 100].doc.getName() != name)
					echoPrint << "\nSorry, room " << room << " is already occupied by " << rooms[room - 100].doc.getName() << "\n";
				else 
				{
					// if room is not taken by another doctor
					echoPrint << "\nDoctor " << doc->getName() << " has been assigned room " << room << "\n";
					rooms[room - 100].doc.setCode(code);
				}
				 // reset vars
				room = 0;
				name = "";
				code = "";
			}

			/******************* doctor check out ******************/
			else if (toupper(inputIO == 'O'))
			{
				// get doc name
				cin.ignore();
				echoPrint << "Type in your name: ";
				getline(cin, name);
				outFile << name;

				// find doc name and room, if they have a waiting list, 
				// move their patients to the next doctors waiting list
				for (int i = 0; i < 100; i++)
				{
					if (rooms[i].doc.getName() == name)
					{
						if (rooms[i].waitingList.getLength() != 0)
						{
							int length = rooms[i].waitingList.getLength();
							for (int j = 0; j < length; j++)
							{
								bool found = false;
								rooms[i].setRoomFree();
								for (int k = 0; k < 100; k++)
								{
									if (rooms[k].getRoomStatus())
									{
										if (!found)
										{
											rooms[i + 1].waitingList.enqueue(rooms[i].waitingList.getForward());
											rooms[i].waitingList.dequeue(rooms[i].waitingList.getForward());
											found = true;
										}
									}
								}
							}
						}
						echoPrint << "You are now checked out.\n";
					}
				}
			}
		}

		/************************ patient check in ******************/
		else if (toupper(inputP) == 'P')
		{
			if (toupper(inputIO == 'I'))
			{
			// get patients name
				cin.ignore();
				echoPrint << "\nType your name: ";
				getline(cin, name);
				outFile << name;
				patPtr->setName(name);

			// get patients age
				echoPrint << "Enter in your age: ";
				cin >> age;
				outFile << age;
				while (age < 0 && age > 150)
				{
					echoPrint << "Invalid age entry.\n"
						<< "Enter in your age: ";
					cin >> age;
					outFile << age;
				}
				patPtr->setAge(age);

			// get patients specialty code - auto-assign PED if under 16
				if (patPtr->getAge() < 16)
				{
					patPtr->setCode("PED");
					code = "PED";
				}
				else
				{
					echoPrint << "Type in your specialist code: ";
					cin >> code;
					outFile << code;
					while (code != "GEN" && code != "INT" && code != "CAR" && code != "SUR"
										 && code != "OBS" && code != "PSY" && code != "NEU" 
										 && code != "ORT" && code != "DET" && code != "OPT" 
										 && code != "ENT")
					{
						echoPrint << "Invalid specialist code."
							<< "Type in your specialist code: ";
						cin >> code;
						outFile << code;
					}
					patPtr->setCode(code);
				}

				// find doctor with specialty code and shortest waiting list
				int indexA  = -1;
				int lengthA = -1;
				int indexB  = -1;
				int lengthB = -1;

				for (int i = 0; i < 100; i++)
				{
					if (patPtr->getCode() == rooms[i].doc.getCode())
					{
						indexA = i;
						lengthA = rooms[i].waitingList.getLength();
					}
				}
				// search again to compare - find shortest waiting list
				bool found = false;
				for (int i = 0; i < 100; i++)
				{
					if (code == rooms[i].doc.getCode())
					{
						indexB = i;
						lengthB = rooms[i].waitingList.getLength();
						found = true;
					}
					// find shorter waiting list
					if (lengthB <= lengthA)
					{
						indexA = indexB;
						lengthA = lengthB;
					}
				}
				// if doc with same spec. code is found, assign doc to patient
				if (found)
				{
					patPtr->setDoc(rooms[indexA].doc);
					rooms[indexA].waitingList.enqueue(newPat);
					echoPrint << "You have been assigned Doctor " << rooms[indexA].doc.getName()
						<< " in room " << rooms[indexA].getRoomNum() << "\n";
				}
				// if no doc with spec. code is found, assign to any doc
				else
				{
					for (int i = 0; i < 100; i++)
					{
						while (!found)
						{
							if (rooms[i].getRoomStatus())
							{
								patPtr->setDoc(rooms[i].doc);
								echoPrint << "You have been assigned Doctor " << rooms[i].doc.getName()
									<< " in room " << rooms[i].getRoomNum() << "\n";
								found = true;
							}
						}
					}
				}
			}

			/************************ patient check out ******************/
			else  if (toupper(inputIO == 'O'))
			{
				// get patient name
				cin.ignore();
				echoPrint << "Type in your name: ";
				getline(cin, name);
				outFile << name;

				// get patient room number
				echoPrint << "Type in your room number: ";
				cin >> room;
				outFile << room;

				if (rooms[room - 100].waitingList.getForwardName() != name)
				{
					echoPrint << "You have not seen the doctor yet, please wait.\n";
				}
				else
				{
					echoPrint << "Thank you for your visit.\nYou are now checked out.\n";
					rooms[room - 100].waitingList.dequeue(rooms[room - 100].waitingList.getForward());
				}
			}
		}

		// prompt user to shutdown system or delay system
		echoPrint << "\nPress any key to continue\n"
			<< "Press Q to shutdown: ";
		cin >> shutDownOption;
		outFile << shutDownOption;
		echoPrint << "\n";
	} while (shutDownOption != 'Q');
	
	outFile.close();
	cout << endl;
	system("pause");
	return 0;
}