// Expense_Program.cpp : Defines the entry point for the console application.
// Christopher Gonzalez
// 3/2/16

#include "stdafx.h"
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//global variables
const int ROWSPACE = 7; //for array
const int COLUMNSPACE = 4; //for double array
int i,j; //used in various loops throughout program

//functions
void getData(string headArray[], string rowArray[], float numArray[][COLUMNSPACE]); //get info from file
void calcTotal(float numArray[][COLUMNSPACE], float totalCtgryArray[], float totalDprtntArray[]); //calcuate total expenses
void getAverage(float numArray[][COLUMNSPACE], float avgCtgryArray[], float avgDprtntArray[]); //calculate average expenses
void printTable(string headArray[], string rowArray[], float numArray[][COLUMNSPACE], 
				float totalCtgryArray[], float totalDprtntArray[], float avgCtgryArray[],
				float avgDprtntArray[]); //printout of data

int _tmain(int argc, _TCHAR* argv[])
{
	string columnNameArray[ROWSPACE]; //array of headers
	string rowNameArray[ROWSPACE]; //array of row names
	float expend[ROWSPACE][COLUMNSPACE]; // array of expenses
	float rowTotal[ROWSPACE]; //array of total expenses of categories
	float columnTotal[COLUMNSPACE]; //array of total expenses of departments
	float rowAverage[ROWSPACE]; //array of average expenses of categories
	float columnAverage[COLUMNSPACE]; //array of average expenses of departments

	getData(columnNameArray, rowNameArray, expend);
	calcTotal(expend, rowTotal, columnTotal);
	getAverage(expend, rowAverage, columnAverage);
	printTable(columnNameArray, rowNameArray, expend, rowTotal, columnTotal, rowAverage, columnAverage);

	system("pause");

	return 0;
}

/* Objective: Reads in data from a file and puts it into arrays
*  Parameters: string headArray[]
*			   string rowArray[]
*			   float numArray[][COLUMNSPACE]
*  Return: N/A
*/
void getData(string headArray[], string rowArray[], float numArray[][COLUMNSPACE])
{
	ifstream expenseFile;

	expenseFile.open("expend.txt");
	//data for header array
	//indexes 0-4 are in the file, indexes 5-6 are for 'Total' and 'Average'
	//of each row
	for(i=0; i<ROWSPACE - 2; i++)
	{
		expenseFile>>headArray[i];
	}
	headArray[5] = "Total";
	headArray[6] = "Average";

	//data for expenses array
	for(i=0; i<ROWSPACE; i++)
	{
		expenseFile>>rowArray[i];
		for(j=0; j<COLUMNSPACE; j++)
		{
			expenseFile>>numArray[i][j];
		}
	}

	expenseFile.close();
}

/* Objective: Calculate the total amount of expenses for each category and each department
*  Parameters: float numArray[][COLUMNSPACE]
*			   float totalCtgryArray[]
*			   float totalDprtntArray[]
*  Return: N/A
*/
void calcTotal(float numArray[][COLUMNSPACE], float totalCtgryArray[], float totalDprtntArray[])
{
	float sum = 0;

	//calculate total for each category
	for(i=0; i<ROWSPACE; i++)
	{
		for(j=0; j<COLUMNSPACE; j++)
		{
			sum += numArray[i][j];
		}
		totalCtgryArray[i] = sum;
	}

	//reset sum to 0
	sum = 0;

	//calculate total for each department
	for(i=0; i<COLUMNSPACE; i++)
	{
		for(j=0; j<ROWSPACE; j++)
		{
			sum += numArray[j][i];
		}
		totalDprtntArray[i] = sum;
	}

}

/* Objective: Calculate the average amount of expenses in each category and each department
*  Parameters: float numArray[][COLUMNSPACE]
*			   float avgCtgryArray[]
*			   float avgDprtntArray[]
*  Return: N/A
*/
void getAverage(float numArray[][COLUMNSPACE], float avgCtgryArray[], float avgDprtntArray[])
{
	float sum = 0;

	//calculate average for each category
	for(i=0; i<ROWSPACE; i++)
	{
		for(j=0; j<COLUMNSPACE; j++)
		{
			sum += numArray[i][j];
		}
		avgCtgryArray[i] = sum / (COLUMNSPACE);
	}

	//reset sum to 0
	sum = 0;

	//calculate average for each department
	for(i=0; i<COLUMNSPACE; i++)
	{
		for(j=0; j<ROWSPACE; j++)
		{
			sum += numArray[j][i];
		}
		avgDprtntArray[i] = sum / (ROWSPACE);
	}


}

/* Objective: Print out the information in a tabluar format
*  Parameters: string headArray[]
*			   string rowArray[]
*			   float numArray[][COLUMNSPACE]
*			   float totalCtgryArray[]
*			   float totalDprtntArray[]
*			   float avgCtgryArray[]
*			   float avgDprtntArray[]
*  Return: N/A
*/
void printTable(string headArray[], string rowArray[], float numArray[][COLUMNSPACE], 
				float totalCtgryArray[], float totalDprtntArray[], float avgCtgryArray[], 
				float avgDprtntArray[])
{
	//header printout
	cout<<left<<setw(5)<<headArray[0];
	for(i=1; i<ROWSPACE; i++)
	{
		cout<<left<<setw(3)<<" "<<headArray[i];
	}

	//row name printout
	for(i=0; i<ROWSPACE; i++)
	{
		cout<<"\n"<<left<<setw(14)<<rowArray[i];
		//expenses printout
		for(j=0; j<COLUMNSPACE; j++)
		{
			cout<<right<<setw(2)<<fixed<<setprecision(2)<<" "<<" $"<<numArray[i][j];
		}
		//total expenses for each category printout
		cout<<setw(5)<<"$"<<totalCtgryArray[i];
		//average expenses for each category printout
		cout<<setw(4)<<"$"<<avgCtgryArray[i];
	}

	//total expenses for each department printout
	cout<<"\n"<<left<<setw(13)<<"Total";
	for(i=0; i<COLUMNSPACE; i++)
	{
		cout<<setw(2)<<fixed<<setprecision(2)<<" "<<" $"<<totalDprtntArray[i];
	}

	//average expenses for each department printout
	cout<<"\n"<<left<<setw(13)<<"Average";
	for(i=0; i<COLUMNSPACE; i++)
	{
		cout<<setw(2)<<fixed<<setprecision(2)<<" "<<" $"<<avgDprtntArray[i];
	}
	cout<<endl;

}