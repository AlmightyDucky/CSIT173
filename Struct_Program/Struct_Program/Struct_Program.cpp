// Struct_Program.cpp : Defines the entry point for the console application.
// Christopher Gonzalez
// 3/9/16

#include "stdafx.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>

using namespace std;

//global variables
const int SIZE_STRUCT = 8; //size of the struct array
const float SALES_TAX = .07; //sales tax for calculating the bill
float tax = 0; //used in the calculateBill function and the printCheck function
int i; //used in various for loops thorughout program

//defines a single item on the menu
struct menuItemType
{
	string menuItem;
	float menuPrice;
	int amtOrdered;
};

//functions
void getData(menuItemType array[]); //gets data from file
void showMenu(menuItemType array[]); //shows menu and allows user to choose items
float calculateBill(menuItemType array[]); //calculates the bill
void printCheck(menuItemType array[], float bill); //prints out the check

int _tmain(int argc, _TCHAR* argv[])
{
	menuItemType menuList[SIZE_STRUCT];
	float customerBill;

	getData(menuList);
	showMenu(menuList);
	customerBill = calculateBill(menuList);
	system("CLS");
	printCheck(menuList, customerBill);

	system("pause");

	return 0;
}

/* Objective: Reads in the menu data from the file and puts it into an array
*  Parameters: menuItemType array[]
*  Return: N/A
*/
void getData(menuItemType array[])
{
	ifstream inFile;
	inFile.open("menuItems.txt");

	//reads in the name of the menu item
	for(i=0; i<SIZE_STRUCT; i++)
	{
		getline(inFile, array[i].menuItem, '\n');
	}

	//reads in the price of the menu item
	for(i=0; i<SIZE_STRUCT; i++)
	{
		inFile>>array[i].menuPrice;
	}

	//initalizes the amount of food a customer orders for use later on
	for(i=0; i<SIZE_STRUCT; i++)
	{
		array[i].amtOrdered = 0;
	}

	inFile.close();
}

/* Objective: Shows the menu and allows customers to pick items they want to
*			  order
*  Parameters: menuItemType array[]
*  Return: N/A
*/
void showMenu(menuItemType array[])
{
	int customerOrder;

	//show the menu
	cout<<setw(30)<<"--------Menu--------"<<endl;
	for(i=0; i<SIZE_STRUCT; i++)
	{
		cout.precision(2); //formats the prices into standard currency format
		cout<<setw(15)<<left<<array[i].menuItem<<" "<<setw(10)<<right<<"$"
			<<fixed<<array[i].menuPrice<<setw(5)<<right<<"["<<i + 1<<"]"<<endl;
	}
	cout<<endl;

	//welcome message
	cout<<"Welcome valued customer! Please select a menu item by typing in\n" 
		<< "the approiate number to the right of the price (without the '[]').\n";
	cout<<"Once you are finished, enter in the number -1.\n"<<endl;

	//user prompt
	cout<<"Enter in a number: ";
	cin>>customerOrder;

	while (customerOrder != -1)
	{
		system("CLS"); //clears the screen

		//show the menu again
		cout<<setw(30)<<"--------Menu--------"<<endl;
		for(i=0; i<SIZE_STRUCT; i++)
		{
			cout.precision(2); //formats the prices into standard currency format
			cout<<setw(15)<<left<<array[i].menuItem<<" "<<setw(10)<<right<<"$"
				<<fixed<<array[i].menuPrice<<setw(5)<<right<<"["<<i + 1<<"]"<<endl;
		}
		cout<<endl;

		//determines which menu item the customer ordered and increments accordingly
		switch (customerOrder)
		{
		case 1: array[customerOrder - 1].amtOrdered ++;
			cout<<array[customerOrder - 1].amtOrdered<<" "
				<<array[customerOrder - 1].menuItem<<" ordered!\n";
			break;
		case 2: array[customerOrder - 1].amtOrdered ++;
			cout<<array[customerOrder - 1].amtOrdered<<" "
				<<array[customerOrder - 1].menuItem<<" ordered!\n";
			break;
		case 3: array[customerOrder - 1].amtOrdered ++;
			cout<<array[customerOrder - 1].amtOrdered<<" "
				<<array[customerOrder - 1].menuItem<<" ordered!\n";
			break;
		case 4: array[customerOrder - 1].amtOrdered ++;
			cout<<array[customerOrder - 1].amtOrdered<<" "
				<<array[customerOrder - 1].menuItem<<" ordered!\n";
			break;
		case 5: array[customerOrder - 1].amtOrdered ++;
			cout<<array[customerOrder - 1].amtOrdered<<" "
				<<array[customerOrder - 1].menuItem<<" ordered!\n";
			break;
		case 6: array[customerOrder - 1].amtOrdered ++;
			cout<<array[customerOrder - 1].amtOrdered<<" "
				<<array[customerOrder - 1].menuItem<<" ordered!\n";
			break;
		case 7: array[customerOrder - 1].amtOrdered ++;
			cout<<array[customerOrder - 1].amtOrdered<<" "
				<<array[customerOrder - 1].menuItem<<" ordered!\n";
			break;
		case 8: array[customerOrder - 1].amtOrdered ++;
			cout<<array[customerOrder - 1].amtOrdered<<" "
				<<array[customerOrder - 1].menuItem<<" ordered!\n";
			break;
		}

		//prompt user again
		cout<<"Enter in another number or -1 to calculate your total: ";
		cin>>customerOrder;
	}
}

/* Objective: Calculates the customer's bill
*  Parameters: menuItemType array[]
*  Return: N/A
*/
float calculateBill(menuItemType array[])
{
	float totalBill = 0;

	//add up the bill before tax
	for(i=0; i<SIZE_STRUCT; i++)
	{
		totalBill += (array[i].menuPrice * array[i].amtOrdered);
	}
	tax = totalBill * SALES_TAX; //determine the tax
	totalBill += tax; //add the tax onto the bill

	return totalBill;
}

/* Objective: Prints out the customer's bill with what they ordered, the amount
*			  the customer ordered, the prices, the tax and their total amount
*			  owed
*  Parameters: menuItemType array[]
*			   float bill
*  Return: N/A
*/
void printCheck(menuItemType array[], float bill)
{
	cout<<setw(30)<<"--------Thank you!--------"<<endl;
	for(i=0; i<SIZE_STRUCT; i++)
	{
		//only prints out the items that the customer ordered
		if(array[i].amtOrdered != 0)
		{
		cout.precision(2); //formats the prices into standard currency format
		cout<<setw(2)<<left<<array[i].amtOrdered<<setw(15)<<left<<array[i].menuItem
			<<setw(10)<<right<<fixed<<"$"<<(array[i].menuPrice * array[i].amtOrdered)<<endl;
		}
	}
	cout<<setw(2)<<" "<<"Tax: "<<setw(20)<<"$"<<tax<<endl; //tax printout
	cout<<setw(2)<<" "<<"Total Amount: "<<setw(11)<<"$"<<bill<<endl; //total amount printout
	cout<<endl;
}