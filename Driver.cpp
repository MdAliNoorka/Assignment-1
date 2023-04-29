#include <iostream>
#include "MemoryManager.h"
using namespace std;

void HomePage();
int StrategeyCheck();
int Menu();

int main()
{
	HomePage();
	system("pause");
	system("cls");
	cout << "\nEntre Total Memory You Have\t";
	int totalMemory = 0;
	cin >> totalMemory;
	bool strat = StrategeyCheck();
	MemoryManagementSystem memoryManager(totalMemory, totalMemory, strat);
	int userInput = 0;
	do
	{
		userInput = Menu();
		if (userInput == 3)
			cout << memoryManager;
		else if (userInput == 1)
		{
			cout << "\nEntre ID\t";
			string id;
			cin.ignore();
			getline(cin, id);
			cout << "\nEntre Memory You Want\t";
			int mem;
			cin >> mem;
			if (strat)
				if (memoryManager.GetMemory(id, mem))
					cout << "\nMemory Allocation : Successfull\n";
				else
					cout << "\nMemory Allocation : Failed\n";

			else
			{
				int a;
				do
				{
					cout << "\n\n\n Entre corrsponding numbers for different commands\n"
						<< "0\t for contigious memory\n"
						<< "1\t for non-contigious memory\n\t";
					cin >> a;
				} while (a != 0 &&  a != 1);
				if (memoryManager.GetMemory(id, mem, a))
					cout << "\nMemory Allocation : Successfull\n";
				else
					cout << "\nMemory Allocation : Failed\n";


				;
			}
			cout << memoryManager;
		}

		else if (userInput == 2)
		{
			int  del = -1;

			do
			{
				cout << "\n\n\n Entre corrsponding numbers for different commands\n"
					<< "0\t for deleting program memory only\n"
					<< "1\t for deleting program memory and deleting data (id name and memory etc) as well\n\t";
				cin >> del;
			} while (del != 0 && del != 1);
			cout << "\nEntre ID\t";
			string id;
			cin.ignore();
			getline(cin, id);
			if (del)
				if ((memoryManager.DeleteAProgram(id)))
					cout << "\n Memory Deletion : Successfull\n";
				else
					cout << "\n Memory Deletion : UnSuccessfull\n";
			else
				if ((memoryManager.DeleteProgramMemoryOnly(id)))
					cout << "\n Memory Deletion : Successfull\n";
				else
					cout << "\n Memory Deletion : UnSuccessfull\n";
			cout << memoryManager;

		}

	} while (userInput != 0);
	memoryManager.Dest();
	cout << memoryManager;



}
void HomePage()
{
	cout << "\n\n\t\t\tWELCOME TO MEMORY MANAGEMENT SYSTEM\n"
		<< "\n\n\n\t\t\t Designed by MUHAMMAD ALI\n"
		<< "\n\n\n\t\t\t \t\t 21L-5463\n"
		<< "\n\n\n For Any Query\n"
		<< "\n Email : l215463@lhr.nu.edu.pk \t |    mdalinoorka@gmail.com"
		<< "\n\n Instagram : mdalinoorka"
		<< " \n\n\n\t\t\t\t";
}

int StrategeyCheck()
{
	int x = -1;
	do
	{
		cout << "\n\t\t\t Entre corrsponding numbers for different commands\n\n"
			<< "0\t For Best Fit Method\n";
		cout << "1\t For First fit method\n\n\t\t";
		cin >> x;
	} while (x > 1 || x < 0);
	return x;
}

int Menu()
{
	int x = -1;
	do
	{
		cout << "\n\t\t\t Entre corrsponding numbers for different commands\n\n"
			<< "1\t to get memory\n"
			<< "2\t to delete memory\n"
			<< "3\t to check the taken and available memory\n"
			<< "0\t to close the meomry manager\n"
			<< "\n\n\t\t\t Your Input : ";
		cin >> x;
	} while (x < 0 || x>3);
	return x;
}



