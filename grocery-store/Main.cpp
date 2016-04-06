#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS // needed to ignore warning about using ctime function

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
using namespace std;

/**************************************
Grocery Store Checkout System

This program simulates a grocery store checkout system. It uses a struct to hold
   a product in the store's inventory, stored in an array. The inventory is uploaded
   through a file Invent.dat. The customer receipts are printed out to a file Receipts.dat.

The product's must be entered manually by the cashier with the product number, followed by the 
   quantity - xxxxx x


Author:		Adam Allard
Created:	06/05/15 - Initial

***************************************/

int main()
{
	class Duplicate
	{ };

	class NotInInventory
	{ };

	class NotInRange
	{ };

	struct Product
	{
		int productNumber = 0;
		string description;
		double price;
		char tax;
	};

	Product productRecords[50];

	/**************************************************************
	read inventory file and process info into productRecords array
	*************************************************************/

	ifstream inFile;
	inFile.open("Invent.dat");

	if (inFile)
	{
		for (int i = 0; i < 50; i++)
		{
			inFile >> productRecords[i].productNumber;
			inFile >> productRecords[i].description;
			inFile >> productRecords[i].price;
			inFile >> productRecords[i].tax;
		}
	}

	inFile.close();

	/*****************************************
	print productRecords array into output file
	*******************************************/

	ofstream receipts;
	receipts.open("Receipts.dat");

	for (int i = 0; i < 50; i++)
	{
		if (productRecords[i].productNumber == 0)
			break;
		receipts << setw(6) << left << productRecords[i].productNumber << setw(13)
			<< productRecords[i].description << setw(5) << setprecision(2) << fixed << showpoint
			<< productRecords[i].price << setw(2)
			<< productRecords[i].tax << endl;
		cout << setw(6) << left << productRecords[i].productNumber << setw(13)
			<< productRecords[i].description << setw(5) << setprecision(2) << fixed << showpoint
			<< productRecords[i].price << setw(2)
			<< productRecords[i].tax << endl;
	}
	cout << endl;


	/*****************************************
	prompting cashier to enter customer orders
	*****************************************/

	const double TAX = .075;

	double unitItemPrice; // price of one item
	double qntyItemPrice; // price times quantity
	double addTax; // added taxes to total
	double salesTotal;

	int num;
	int qnty;

	bool found; // is item found in inventory
	bool taxed; // is item taxed
	bool done;  // is cashier done entering product numbers

	char again; // is there another customer

	int custNum = 0; // customer accumulator

	do
	{
		found = false;
		taxed = false;
		done = false;
		custNum++;
		unitItemPrice = 0;
		qntyItemPrice = 0;
		addTax = 0;
		salesTotal = 0;

		// print date and time to receipt
		cout << endl;
		time_t now = time(0);
		char* dt = ctime(&now);
		receipts << endl << dt << "Customer " << custNum;

		cout << "Enter customer order - product number followed by quantity - 0 when finished:" << endl;

		if (qnty < 1 || qnty > 100)
			throw NotInRange();

		try
		{
			cin >> num;
			cin >> qnty;
		}
		catch (NotInRange())
		{
			receipts << endl << "Quantity not in range.";
		}


		while (!done)
		{
			found = false;
			taxed = false;

			for (int i = 0; i < 50; i++)
			{
				if (productRecords[i].productNumber == num)
				{
					found = true;

					unitItemPrice = productRecords[i].price;
					qntyItemPrice = unitItemPrice * qnty;

					if (productRecords[i].tax == 'T')
					{
						taxed = true;
						addTax = TAX * qntyItemPrice;
					}

					salesTotal += qntyItemPrice;

					// print item info to receipt
					receipts << endl;
					receipts << setw(14) << left << productRecords[i].description << qnty << " @ " << unitItemPrice << " " << qntyItemPrice;
					if (taxed)
						receipts << "\tTX";
				}
			}
			if (!found)
				receipts << endl << "***item " << num << " not in inventory***";


			// cashier entering in another product number. if 0, customer has no more products
			cin >> num;
			if (num == 0)
				done = true;
			else
				cin >> qnty;
		}

		// once no more products, print totals to receipt
		receipts << endl;
		receipts << "\tSubtotal: " << salesTotal << endl
			<< "\tTax:      " << addTax << endl << endl
			<< "\tTotal:    " << salesTotal + addTax << endl;



		cout << "Do you have another customer order to process? (Y/N): ";
		cin >> again;
	} while (again == 'Y' || again == 'y');


	receipts.close();



	cout << endl;
	system("pause");
	return 0;
}
#endif