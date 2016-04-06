/*

CISS 350 Programming Assignment 3
Local Medical Clinic sheduling service.

This program will allow doctors and patients to check in to the hospital.
The hospital has a 100 rooms.
Doctors can check in and request a specific room.
When a patient checks in, they will automatically be assigned a doctor based upon the specialty they have requested.
The rules for assigning doctors to patients are as follows:
1.	Any patient under age 16 is assigned to see a pediatrician.
2.	Patients age 16 and older are assigned a doctor according to the specialty requested. If there is no doctor in the clinic with the requested specialty, the patient is assigned to a general practitioner (GP). If there is no GP, the patient can be assigned to any doctor.
3.	If there is more than one doctor of the requested specialty, the patient is assigned to the doctor with the shortest waiting list.

When a patient checks out, the doctor he or she was assigned to is available to see the next patient, if there is anyone in the waiting list.

In addition to printing the messages on the screen, the program will also write the requests and messages to a transaction file (trans.out).

The following assumptions are made:
1.	No patient leaves without checking out.
2.	No one leaves before he or she sees the assigned doctor.
3.	If a doctor checks out while there is still a waiting list of patients assigned to him or her, the patients are reassigned to other doctors.

*/


#include <iostream>
#include <string>
#include <Windows.h>		// For changing console colors.
#include <fstream>
#include <time.h>			// For the date and time.
#include "LinkedQue.h"
using namespace std;


// Function Prototypes
int getSpecialty();
void displayIntro();
void doctorCheckIn();
void doctorCheckOut();
int displayMenu();
int getRoomNumber();
void patientCheckIn();
void patientCheckOut();
void showActiveRooms();
void assignDoctor(patient&);
void openOutputFile();

// A struct that holds the information for a doctor.
struct doctor {
	string name;
	int favRoomNum;
	int specialty;
};

// A struct that represents a hospital room.
struct hospitalRoom {
	bool doctorIn;
	bool patientIn;
	LinkedQue waitingRoom;
	patient p;
	doctor d;
};

// Declare Global Variables for use by all.
hospitalRoom hRoom[100];		// Creates an array of 100 hospital rooms.
ofstream trans;			// Used to write all screen input and ouput to a file.

int main()
{

	// Open the output file.  It will be used to record information about the session.
	openOutputFile();

	int menuChoice = 0; // A variable that holds the user's menu choice.

	displayIntro();	// Display the intro and instructions to the user.

	// While the user does not choose to exit (6).
	while (menuChoice != 6)
	{
		menuChoice = displayMenu(); // Use the displayMenu function to get the user's choice.

		// Check in a doctor.
		if (menuChoice == 1)
		{
			doctorCheckIn();
		}
		// Check out a doctor.
		else if (menuChoice == 2)
		{
			doctorCheckOut();
		}
		// Check in a patient.
		else if (menuChoice == 3)
		{
			patientCheckIn();
		}
		// Check out a patient.
		else if (menuChoice == 4)
		{
			patientCheckOut();
		}
		// Show the active rooms being used.
		else if (menuChoice == 5)
		{
			showActiveRooms();
		}
		// Exit the program.
		else if (menuChoice == 6)
		{
			cout << "\n\tPROGRAM ENDING......" << endl;
			cout << "\tGOODBYE!" << endl;

			trans << "\n\tPROGRAM ENDING......" << endl;
			trans << "\tGOODBYE!" << endl;
			exit(0);
		}
	}

	return 0;
}

//******************************************************************************************
// The getSpecialty function accepts no arguments.  It will display a list of doctor
// specialties and get the user's choice.  It will return that choice, an  int.
//******************************************************************************************
int getSpecialty()
{
	int choice; // Holds the value of the user's choice.

	cout << "Please choose a specialty from the list below:" << endl;
	cout << "\t1.  PED  Pediatrics" << endl;
	cout << "\t2.  GEN  General Practice" << endl;
	cout << "\t3.  INT  Internal Medicine" << endl;
	cout << "\t4.  CAR  Cardiology" << endl;
	cout << "\t5.  SUR  Surgeon" << endl;
	cout << "\t6.  OBS  Obstetrics" << endl;
	cout << "\t7.  PSY  Psychiatry" << endl;
	cout << "\t8.  NEU  Neurology" << endl;
	cout << "\t9.  ORT  Orthopedics" << endl;
	cout << "\t10. DET  Dermatology" << endl;
	cout << "\t11. OPT  Ophthalmology" << endl;
	cout << "\t12. ENT  Ear, Nose, and Throat" << endl;
	cout << "ENTER CHOICE: ";

	trans << "Please choose a specialty from the list below:" << endl;
	trans << "\t1.  PED  Pediatrics" << endl;
	trans << "\t2.  GEN  General Practice" << endl;
	trans << "\t3.  INT  Internal Medicine" << endl;
	trans << "\t4.  CAR  Cardiology" << endl;
	trans << "\t5.  SUR  Surgeon" << endl;
	trans << "\t6.  OBS  Obstetrics" << endl;
	trans << "\t7.  PSY  Psychiatry" << endl;
	trans << "\t8.  NEU  Neurology" << endl;
	trans << "\t9.  ORT  Orthopedics" << endl;
	trans << "\t10. DET  Dermatology" << endl;
	trans << "\t11. OPT  Ophthalmology" << endl;
	trans << "\t12. ENT  Ear, Nose, and Throat" << endl;
	trans << "ENTER CHOICE: ";

	// Get the user's choice.
	cin >> choice;
	trans << choice;

	// Validate the user's choice.
	while (choice < 1 || choice > 12)
	{
		cout << "INVALID ENTRY! Please try again." << endl;
		cout << "ENTER CHOICE: ";

		trans << "INVALID ENTRY! Please try again." << endl;
		trans << "ENTER CHOICE: ";

		cin >> choice;
		trans << choice;
	}

	// Return the choice.
	return choice;
}

//*************************************************************************************
// The displayIntro funcion accepts no arguments.  It will display the introduction
// and instructions on how to use the program.
//*************************************************************************************
void displayIntro()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (12 + (1 * 16))); // Set the text color to red.
	cout << "\t***************************************\t\t" << endl;
	cout << "\t**       MEDICAL CLINIC PROGRAM      **\t\t" << endl;
	cout << "\t***************************************\t\t\n\n" << endl;

	trans << "\t***************************************\t\t" << endl;
	trans << "\t**       MEDICAL CLINIC PROGRAM      **\t\t" << endl;
	trans << "\t***************************************\t\t\n\n" << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14 + (0 * 16))); // Set the text color to yellow.
	cout << "\t-INSTRUCTIONS-" << endl;
	cout << " This program will simulate a hospital." << endl;
	cout << " There are a 100 rooms in this hospital." << endl;
	cout << " The doctor's can request their own rooms that they would like to use." << endl;
	cout << " Patients will automatically be assigned a doctor when the check in based upon" << endl;
	cout << " the specialty code put in." << endl;
	cout << " As long as there is a doctor, the patient will be assigned one." << endl;
	cout << " A patient will not be able to check in unless there is a doctor checked in." << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (15 + (0 * 16))); // Set the text color to white.

}

//*************************************************************************************
// The doctorCheckIn function accepts no arguments.  It will use the recursive function
// getRoomNumber to get the doctor a room to work from. Then it will get the rest of
// the doctors information, including their name and specialty code.
//*************************************************************************************
void doctorCheckIn()
{
	cout << "\n\tDOCTOR CHECK IN" << endl;
	trans << "\n\tDOCTOR CHECK IN" << endl;

	// The variable roomNumber will hold the value returned by the getRoomNumber function.
	int roomNumber = getRoomNumber();

	cin.ignore();

	// Get the doctor's name.
	cout << "Please enter the doctors name: ";
	trans << "Please enter the doctors name: ";

	getline(cin, hRoom[roomNumber].d.name);
	trans << hRoom[roomNumber].d.name;

	// Get the doctor's specialty.
	hRoom[roomNumber].d.specialty = getSpecialty();

}

//*******************************************************************************************
// The doctorCheckOut function accepts no arguments.  It will get a room number from 
// which a doctor is checking out of.  If there is not a doctor in the room, the user
// will be notified.  Otherwise the doctor is removed from the room.  If there are 
// patients in the room, they will be reassigned a doctor using the assignDoctor function.
//*******************************************************************************************
void doctorCheckOut()
{
	// Hold the value of a room number.
	int roomNum;

	// Get a room number from the user from which the doctor is checking out of.
	cout << "Please enter the room number from which" << endl;
	cout << "the doctor will be checking out: ";

	trans << "Please enter the room number from which" << endl;
	trans << "the doctor will be checking out: ";

	cin >> roomNum;
	trans << roomNum;

	// Validate the user input.
	while (roomNum < 0 || roomNum	> 100)
	{
		cout << "INVALID ENTRY! Enter a room number between 1 and 100." << endl;
		cout << "Enter the room number: ";

		trans << "INVALID ENTRY! Enter a room number between 1 and 100." << endl;
		trans << "Enter the room number: ";

		cin >> roomNum;
		trans << roomNum;
	}

	// Correct the room number to represent a position in the array.
	roomNum = roomNum - 1;

	// If there is not a doctor in the room, notify the user.
	if (hRoom[roomNum].doctorIn == false)
	{
		cout << "There was not a doctor in room #" << roomNum + 1 << "." << endl;
		trans << "There was not a doctor in room #" << roomNum + 1 << "." << endl;

	}
	// Else, set doctor to false.
	else
	{
		hRoom[roomNum].doctorIn = false;
		cout << "Doctor " << hRoom[roomNum].d.name << " is now checked out of the room." << endl;
		trans << "Doctor " << hRoom[roomNum].d.name << " is now checked out of the room." << endl;

		// Check the waiting room.
		// If the waiting room is empty, notify the user and do nothing.
		if (hRoom[roomNum].waitingRoom.IsEmpty())
		{
			cout << " There are no patients in the waiting room to move." << endl;
			trans << " There are no patients in the waiting room to move." << endl;

		}
		// Else, the room has patients and they need to be moved to another room with doctors.
		else
		{
			int numPeople = hRoom[roomNum].waitingRoom.GetLength();	// Holds the value of the number of people in the que.

			// A for loop that will get a patient from the doctor's waiting room que, and assign them to another doctor.
			for (int i = 0; i < numPeople; i++)
			{
				patient tempPatient;	// Used to hold a patient.
				hRoom[roomNum].waitingRoom.Dequeue(tempPatient);	// Deque a patient from the waiting room.
				cout << "\n -ASSIGNING PATIENT " << i + 1 << ": " << tempPatient.name;
				trans << "\n -ASSIGNING PATIENT " << i + 1 << ": " << tempPatient.name;


				// Pass the patient to the assignDoctor function.
				assignDoctor(tempPatient);
			}

		}

	}

}

//************************************************************************************************
//  The displayMenu function accedts no arguments. It will get the user's menu choice and return
//  it.
//************************************************************************************************
int displayMenu()
{
	int choice = 0;	// Hold the user's choice.

	// Get the user's menu choice.
	cout << "\n\tMENU" << endl;
	cout << " 1. Doctor Check-In" << endl;
	cout << " 2. Doctor Check-Out" << endl;
	cout << " 3. Patient Check-In" << endl;
	cout << " 4. Patient Check-Out" << endl;
	cout << " 5. Show Active Rooms" << endl;
	cout << " 6. Exit" << endl;
	cout << " Enter choice: ";

	trans << "\n\tMENU" << endl;
	trans << " 1. Doctor Check-In" << endl;
	trans << " 2. Doctor Check-Out" << endl;
	trans << " 3. Patient Check-In" << endl;
	trans << " 4. Patient Check-Out" << endl;
	trans << " 5. Show Active Rooms" << endl;
	trans << " 6. Exit" << endl;
	trans << " Enter choice: ";

	cin >> choice;
	trans << choice << endl;

	// Validate the user's input.
	while (choice < 1 || choice > 6)
	{
		cout << " INVALID ENTRY! Try again." << endl;
		cout << " Enter choice: ";

		trans << " INVALID ENTRY! Try again." << endl;
		trans << " Enter choice: ";

		cin >> choice;
		trans << choice << endl;
	}

	return choice;
}

//***************************************************************
// The function getRoomNumber is a recursive function that will 
// get the user input for a room number that a doctor wants.
// If the room is not available, the function will repeat until
// they choose a room that is available.
//***************************************************************
int getRoomNumber()
{
	int roomNumber; // Hold the value of a room number.

	// Get a room number from the user.
	cout << "\nEnter the room number to check into (1-100): ";
	trans << "\nEnter the room number to check into (1-100): ";

	cin >> roomNumber;
	trans << roomNumber << endl;

	// Validate the user input.
	while (roomNumber < 0 || roomNumber > 100)
	{
		cout << "INVALID ENTRY! Try again." << endl;
		cout << "\nWhat room will the doctor be checking into? (1-100): ";

		trans << "INVALID ENTRY! Try again." << endl;
		trans << "\nWhat room will the doctor be checking into? (1-100): ";

		cin >> roomNumber;
		trans << roomNumber << endl;
	}

	// Since the room number will represent a spot in the array, subtract 1.
	roomNumber = roomNumber - 1;

	// If the room does not have a doctor.
	if (hRoom[roomNumber].doctorIn == false)
	{
		cout << "Room #" << roomNumber + 1 << " is available." << endl;
		trans << "Room #" << roomNumber + 1 << " is available." << endl;

		hRoom[roomNumber].doctorIn = true; // Set the doctorIn to true.
		return roomNumber; // Return the room number.
	}
	// Else the there is a doctor already in that room.
	else
	{
		// Tell the user the room is not available.
		cout << "Room #" << roomNumber + 1 << " is NOT available. Try again." << endl;
		trans << "Room #" << roomNumber + 1 << " is NOT available. Try again." << endl;

		// Call the function again.
		getRoomNumber();
	}

}

//**************************************************************************************************
// The patientCheckIn function accepts no arguments.  It will get user input on information from a
// patient.  It will then call the assignDoctor function to assign the patient to a doctor.
//**************************************************************************************************
void patientCheckIn()
{

	patient tempPatient;		// Used to hold patient information.

	// Get the patient's name.
	cout << "\nPlease enter the patient's name: ";
	trans << "\nPlease enter the patient's name: ";

	cin.ignore();
	getline(cin, tempPatient.name);
	trans << tempPatient.name << endl;

	// Get the patient's age.
	cout << "Please enter the patient's age: ";
	trans << "Please enter the patient's age: ";

	cin >> tempPatient.age;
	trans << tempPatient.age << endl;

	// Get a short description on the patient's issue.
	cout << "Please enter a short descritpion for the patient's issue, 20 characters max:" << endl;
	trans << "Please enter a short descritpion for the patient's issue, 20 characters max:" << endl;

	cin.ignore();
	getline(cin, tempPatient.emergencyDescription);
	trans << tempPatient.emergencyDescription << endl;

	// Validate the user's input is less than 20 characters.
	while (tempPatient.emergencyDescription.length() > 20)
	{
		cout << "INVALID ENTRY! Too many characters. Try again below." << endl;
		trans << "INVALID ENTRY! Too many characters. Try again below." << endl;

		cin >> tempPatient.emergencyDescription;
		trans << tempPatient.emergencyDescription << endl;
	}

	// Get a specialty code on the patient's condition.
	tempPatient.specialty = getSpecialty();

	// Assign the patient to a doctor.
	assignDoctor(tempPatient);

}

//*************************************************************************************************
// The patientCheckOut function does not accept any arguments.  It will get the room number from
// which the patient is checking out of.  If the room entered is empty, it will notify the user.
//
// Since the assumption is that a patient does not check out until being seen by a doctor, and
// all patients check out, the first patient in the que is checked out.
//*************************************************************************************************
void patientCheckOut()
{
	cout << "\n\tPATIENT CHECK OUT" << endl;
	trans << "\n\tPATIENT CHECK OUT" << endl;

	int roomNumber;		// Hold the value of a room number.
	patient tempPatient;	// Hold information about a patient.

	// Get the room number.
	cout << "\n Please enter the room number: ";
	trans << "\n Please enter the room number: ";

	cin >> roomNumber;
	trans << roomNumber << endl;

	// Validate the user input.
	while (roomNumber < 0 || roomNumber > 100)
	{
		cout << "INVALID ENTRY! Try again." << endl;
		cout << " Please enter the room number: ";

		trans << "INVALID ENTRY! Try again." << endl;
		trans << " Please enter the room number: ";

		cin >> roomNumber;
		trans << roomNumber << endl;
	}

	// Correct the roomNumber to properly represent an element in the array.
	roomNumber = roomNumber - 1;

	// If the waiting room is empty.
	if (hRoom[roomNumber].waitingRoom.IsEmpty())
	{
		cout << " ** There are no patients in room #" << roomNumber + 1 << ". **" << endl;
		trans << " ** There are no patients in room #" << roomNumber + 1 << ". **" << endl;

	}
	// Else the first patient in the waiting room que has been seen and is checking out.
	else
	{
		// Deque the patient.
		hRoom[roomNumber].waitingRoom.Dequeue(tempPatient);

		// Display the patient information.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14 + (0 * 16))); // Set the text color to yellow.

		cout << "\n-------------------------------------------------------" << endl;
		cout << "The following patient has checked out:" << endl;
		cout << "ROOM #: " << (roomNumber + 1) << endl;
		cout << "PATIENT NAME: " << tempPatient.name << endl;
		cout << "-------------------------------------------------------\n" << endl;

		trans << "\n-------------------------------------------------------" << endl;
		trans << "The following patient has checked out:" << endl;
		trans << "ROOM #: " << (roomNumber + 1) << endl;
		trans << "PATIENT NAME: " << tempPatient.name << endl;
		trans << "-------------------------------------------------------\n" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (15 + (0 * 16))); // Set the text color to white.

	}

}

//*************************************************************************************************
// The showActtiveRooms function does not accept any arguments. I will display all rooms that have
// a doctor checked into them, and the number of patients in the waiting room.
//*************************************************************************************************
void showActiveRooms()
{
	bool activeRooms = false;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14 + (0 * 16))); // Set the text color to yellow.

	// A for loop that will search each room for a doctor.
	cout << "\n-------------------------------------------------------" << endl;
	trans << "\n-------------------------------------------------------" << endl;

	// A for loop that will go through each hospital room.
	for (int i = 0; i < 100; i++)
	{

		// An if statement that will execute if a doctor is in the room.
		if (hRoom[i].doctorIn == true)
		{
			// Display the information about the room.
			cout << "ROOM #: " << i + 1 << endl;
			cout << "DOCTOR: " << hRoom[i].d.name << endl;
			cout << "SPECIALTY: " << hRoom[i].d.specialty << endl;

			trans << "ROOM #: " << i + 1 << endl;
			trans << "DOCTOR: " << hRoom[i].d.name << endl;
			trans << "SPECIALTY: " << hRoom[i].d.specialty << endl;

			// Display patient information.
			// If there are no patients.
			if (hRoom[i].patientIn == false)
			{
				cout << "PATIENTS: No" << endl;
				trans << "PATIENTS: No" << endl;
			}
			// Else there are patients.
			else
			{
				cout << "PATIENTS: " << hRoom[i].waitingRoom.GetLength() << endl;
				trans << "PATIENTS: " << hRoom[i].waitingRoom.GetLength() << endl;

			}
			cout << "-------------------------------------------------------" << endl;
			trans << "-------------------------------------------------------" << endl;

			// If there are rooms, this is set to true.
			activeRooms = true;
		}
	}

	// If there are no active rooms, display the following information.
	if (activeRooms == false)
	{
		cout << "THERE ARE NO ACTIVE ROOMS" << endl;
		cout << "-------------------------------------------------------\n" << endl;

		trans << "THERE ARE NO ACTIVE ROOMS" << endl;
		trans << "-------------------------------------------------------\n" << endl;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (15 + (0 * 16))); // Set the text color to white.

}

//********************************************************************************************************
// The assignDoctor accepts a reference to a patient variable. It will use a series of if statements
// and for loops to search each hospital room for a doctor that matches the patients specialty needed.
// If the specialty can not be found, then a General Practice doctor will be assigned. If there are no
// General Practice doctors, than the doctor with the smallest waiting room will be assigned.
// If there are no doctors than the user will be notified and the patient will not be pushed into a que.
//********************************************************************************************************
void assignDoctor(patient& tempP)
{
	bool doctorFound = false; // Used to indicate whether a doctor is in a room or not.

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (14 + (0 * 16))); // Set the text color to yellow.

	// If the patient is 16 or younger, see a pediatrician.
	if (tempP.age < 17)
	{

		// A for loop that will search each room for a doctor.
		for (int i = 0; i < 100; i++)
		{

			// An if statement that will execute if a doctor is in the room.
			if (hRoom[i].doctorIn == true)
			{

				// An if statement that will execute if the doctor in the room is a pediatrician.
				if (hRoom[i].d.specialty == 1)
				{

					cout << "\n-------------------------------------------------------" << endl;
					cout << "Please direct the patient to the following room:" << endl;
					cout << "ROOM #: " << i + 1 << endl;
					cout << "DOCTOR: " << hRoom[i].d.name << endl;
					cout << "-------------------------------------------------------" << endl;

					trans << "\n-------------------------------------------------------" << endl;
					trans << "Please direct the patient to the following room:" << endl;
					trans << "ROOM #: " << i + 1 << endl;
					trans << "DOCTOR: " << hRoom[i].d.name << endl;
					trans << "-------------------------------------------------------" << endl;

					// Enque the patient.
					hRoom[i].waitingRoom.Enqueue(tempP);
					// Set patientIn to true to indicate that there is a patient in the room.
					hRoom[i].patientIn = true;
					// Set doctorFound to true.
					doctorFound = true;
					break;
				}
			}
		}

		// If there was not a pediatric doctor available, notify the user and move on to the next search algorithm.
		if (doctorFound == false)
		{
			cout << " ** There is no pediatric doctor available. **" << endl;
			cout << " ** Searching for another doctor. **" << endl;

			trans << " ** There is no pediatric doctor available. **" << endl;
			trans << " ** Searching for another doctor. **" << endl;
		}

	}

	// If the patient is older than 16, or the pateint was less that 17 and there was not pediatric doctor.
	if (tempP.age > 17 || doctorFound == false)
	{

		// A for loop that will search each room for a doctor.
		for (int i = 0; i < 100; i++)
		{

			// An if statement that will execute if a doctor is in the room.
			if (hRoom[i].doctorIn == true)
			{

				// An if statement that will execute if the doctor in the room matches the patient's requested specialty.
				if (hRoom[i].d.specialty == tempP.specialty)
				{
					// NEED TO VERIFY THAT THIS DOCTOR HAS THE SMALLEST WAITING LIST.
					int tempRoom;		//Hold the value of a room number that has the lowest amount of people waiting.
					int waitR1;		//Hold the value of the number of people in the waiting room currently being searched.
					int lowestRoomFoundYet = 100;	//Hold the value of the value of the room with the lowest number found yet.  Start at 100 a decrease as waiting rooms with people are found.

					for (int count = 0; count < 100; count++)
					{

						if (hRoom[count].doctorIn == true)
						{
							if (hRoom[count].d.specialty == tempP.specialty)
							{
								// Set the waitR1 variable to the size of the que.
								waitR1 = hRoom[count].waitingRoom.GetLength();

								// If the current room is less than the smalles room found yet, set the tempRoom to i (the currrent room) and set the lowest room found yet variable to the current que size.
								if (waitR1 <= lowestRoomFoundYet)
								{
									tempRoom = count;
									lowestRoomFoundYet = waitR1;
								}
							}
						}
					}

					// The room that matches the patient's requested specialty that has the smalles que is tempRoom.
					// Assign the patient to the doctor.

					cout << "\n-------------------------------------------------------" << endl;
					cout << "Please direct the patient to the following room:" << endl;
					cout << "ROOM #: " << (tempRoom + 1) << endl;
					cout << "DOCTOR: " << hRoom[tempRoom].d.name << endl;
					cout << "-------------------------------------------------------" << endl;

					trans << "\n-------------------------------------------------------" << endl;
					trans << "Please direct the patient to the following room:" << endl;
					trans << "ROOM #: " << (tempRoom + 1) << endl;
					trans << "DOCTOR: " << hRoom[tempRoom].d.name << endl;
					trans << "-------------------------------------------------------" << endl;

					// Enque the patient.
					hRoom[tempRoom].waitingRoom.Enqueue(tempP);
					// Set patientIn to true.
					hRoom[tempRoom].patientIn = true;
					// Set doctorFound to true.
					doctorFound = true;
					break;
				}
			}
		}

		// If a doctor with a specialty was not found, this statement will execute.
		// It will locate a doctor with a General Practice Specialty.
		if (doctorFound == false)
		{
			for (int i = 0; i < 100; i++)
			{

				// An if statement that will execute if a doctor is in the room.
				if (hRoom[i].doctorIn == true)
				{

					// An if statement that will execute if the doctor in the room is a GEN doctor.
					if (hRoom[i].d.specialty == 2)
					{

						cout << "\n-------------------------------------------------------" << endl;
						cout << "Please direct the patient to the following room:" << endl;
						cout << "ROOM #: " << i + 1 << endl;
						cout << "DOCTOR: " << hRoom[i].d.name << endl;
						cout << "-------------------------------------------------------" << endl;

						trans << "\n-------------------------------------------------------" << endl;
						trans << "Please direct the patient to the following room:" << endl;
						trans << "ROOM #: " << i + 1 << endl;
						trans << "DOCTOR: " << hRoom[i].d.name << endl;
						trans << "-------------------------------------------------------" << endl;

						// Enque the patient.
						hRoom[i].waitingRoom.Enqueue(tempP);
						/// Set patientIn to true.
						hRoom[i].patientIn = true;
						// Set doctor found to true.
						doctorFound = true;
						break;
					}
				}
			}
		}

		// If there still is not a doctor found that matches the patients needed specialty, and no GP doctor, assign to a doctor who has the smallest waiting room que.
		if (doctorFound == false)
		{
			int tempRoom;		//Hold the value of a room number that has the lowest amount of people waiting.
			int waitR1;		//Hold the value of the number of people in the waiting room currently being searched.
			int lowestRoomFoundYet = 100;	//Hold the value of the value of the room with the lowest number found yet.  Start at 100 a decrease as waiting rooms with people are found.

			// Search through all 100 hospital rooms.
			for (int i = 0; i < 100; i++)
			{
				// If a room has a doctor in it, check the waiting room que length.
				if (hRoom[i].doctorIn == true)
				{
					// Set the waitR1 variable to the size of the que.
					waitR1 = hRoom[i].waitingRoom.GetLength();

					// If the current room is less than the smalles room found yet, set the tempRoom to i (the currrent room) and set the lowest room found yet variable to the current que size.
					if (waitR1 <= lowestRoomFoundYet)
					{
						tempRoom = i;
						lowestRoomFoundYet = waitR1;
					}

				}

			}

			// Display the information to the user.
			cout << "\n-------------------------------------------------------" << endl;
			cout << "Please direct the patient to the following room:" << endl;
			cout << "ROOM #: " << tempRoom + 1 << endl;
			cout << "DOCTOR: " << hRoom[tempRoom].d.name << endl;
			cout << "-------------------------------------------------------" << endl;

			trans << "\n-------------------------------------------------------" << endl;
			trans << "Please direct the patient to the following room:" << endl;
			trans << "ROOM #: " << tempRoom + 1 << endl;
			trans << "DOCTOR: " << hRoom[tempRoom].d.name << endl;
			trans << "-------------------------------------------------------" << endl;

			// Enque the patient.
			hRoom[tempRoom].waitingRoom.Enqueue(tempP);
			hRoom[tempRoom].patientIn = true;
			doctorFound = true;
		}

		// If a doctor still has not been found, then there is no doctor in the hospital.
		if (doctorFound == false)
		{
			cout << "\n**There is no doctor available to see this patient.**\n" << endl;
			trans << "\n**There is no doctor available to see this patient.**\n" << endl;

		}

	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (15 + (0 * 16))); // Set the text color to white.

}

//*****************************************************************************************************
// The openOutputFile does not accept any arguments. It will open a text file to append input and 
// output to it.  It will write the time and date to the file to indicate the beginning of a session.
//*****************************************************************************************************
void openOutputFile()
{
	trans.open("trans.out", ios::app);						// Open the inventory file.
	// Check to see if the file opened. If it has not opened, tell the user and exit the program.
	if (!trans.is_open())
	{
		cout << "FATAL PROGRAM ERROR: The Dates.out file could not be located." << endl;
		cout << "Program terminating...." << endl;

		trans << "FATAL PROGRAM ERROR: The Dates.out file could not be located." << endl;
		trans << "Program terminating...." << endl;

		exit(0);
	}

	// Insert the time into the output file for record keeping.
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	// timeinfo = localtime(&rawtime);
	trans << endl;
	trans << "************************** N E W    S E S S I O N **************************" << endl;
	trans << "\t\t\t  (time)" ;
	trans << "****************************************************************************" << endl;
	trans << endl;

}