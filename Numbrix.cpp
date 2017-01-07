
#include "Numbrix.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <string>
#include <sstream>

using std::cout;
using std::cin;
using std::endl;

Numbrix::Numbrix()
{
	readInput();
}

Numbrix::~Numbrix()
{
	delete[] numbArr;
	delete[] cpyArr;
}

void Numbrix::readInput()

	std::string str = "";
	int size = 0, y = 0, x = 0, val = 0;
	bool isPass = false;
	while (!isPass)
	{
		cout << "Enter the number of squares in the puzzle: ";
		getline(cin, str);
		convertStr(&str, &size, &isPass);
	}
	isPass = false;
	str = "y";
	initializeArr(sqrt(size));
	numbArr[0][1] = 42;
	cout << "For example, " << endl;
	print();
	cout << endl << "the location of 42 would be y = 0, x = 1, where the bottom squares start with y = 0, " << endl;
	cout << "and the left most squares start with x = 0" << endl;
	numbArr[0][1] = 0;
	cout << "You can re-enter the coordinates and the values if mistake is made." << endl;
	cout << "Now enter the starting numbers and their coordinates" << endl << endl;
	while (str == "y" || str == "Y")
	{
		str = "";
		while (!isPass)
		{
			cout << "Enter the y-coordinate: ";
			getline(cin, str);
			convertStr(&str, &y, &isPass);
			isPass = checkBounds(y);
		}
		isPass = false;
		while (!isPass)
		{
			cout << "Enter the x-coordinate: ";
			getline(cin, str);
			convertStr(&str, &x, &isPass);
			isPass = checkBounds(x);
		}
		isPass = false;
		while (!isPass)
		{
			cout << "Enter the number: ";
			getline(cin, str);
			convertStr(&str, &val, &isPass);
		}
		isPass = false;
		cpyArr[y][x] = numbArr[y][x] = val;
		presets.push_back(val);
		cout << endl << "Continue? y/Y to continue or any other keys if done" << endl;
		cin >> str;
		cin.clear();
		cin.ignore();
	}
}

void Numbrix::convertStr(std::string* str, int* rtnVal, bool* isPass)
{
	std::stringstream convVal(*str);
	if (convVal >> *rtnVal && !(convVal >> *str))
	{
		*isPass = true;
		*str = "";
	}
	else
		cout << "Invalid input. ";
}

bool Numbrix::checkBounds(int val)
{
	if (val >= 0 && val < n)
		return true;
	else
	{
		cout << "Invalid input. ";
		return false;
	}
}

void Numbrix::initializeArr(int size)
{
	this->n = size;    
	numbArr = new int*[n]; 
	for (int i = 0; i < n; i++)
		numbArr[i] = new int[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			numbArr[i][j] = 0; 
	
	cpyArr = new int*[n];
	for (int i = 0; i < n; i++)
		cpyArr[i] = new int[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cpyArr[i][j] = 0;
}

void Numbrix::findSol()
{
	int temp = findFirstNum(); 
	int startI = temp / n;  
	int startJ = temp % n;  
	int startVal = numbArr[startI][startJ];    
	
	if (startVal == 1)
	{
		findSol(startI, startJ, startVal);  
	}
	else
	{
		for (int i = n - 1; i >= 0; i--)
		{
			for (int j = 0; j < n; j++)
			{
				if (numbArr[i][j] == 0)
				{
					findSol(i, j, 1);   
					redrawGrid(fileName);  
				}
			}
		}
	}
}

void Numbrix::findSol(int i, int j, int num)    
{
	if (i < 0 || i > n - 1 || j < 0 || j > n - 1)   
		return;
	
	numbArr[i][j] = num;    
	
	if (num == n * n)  
	{
		print();
		return;
	}

	if (j - 1 >= 0 && numbArr[i][j - 1] == num + 1)
		findSol(i, j - 1, num + 1);   
	if (j + 1 < n && numbArr[i][j + 1] == num + 1)
		findSol(i, j + 1, num + 1);    
	if (i - 1 >= 0 && numbArr[i - 1][j] == num + 1)
		findSol(i - 1, j, num + 1);     
	if (i + 1 < n && numbArr[i + 1][j] == num + 1)
		findSol(i + 1, j, num + 1);    
	
	if (j - 1 >= 0 && numbArr[i][j - 1] == 0 && !isPreset(num + 1))
		findSol(i , j - 1, num + 1);  
	if (j + 1 < n && numbArr[i][j + 1] == 0 && !isPreset(num + 1))
		findSol(i, j + 1, num + 1);   
	if (i - 1 >= 0 && numbArr[i - 1][j] == 0 && !isPreset(num + 1))
		findSol(i - 1, j, num + 1);    
	if (i + 1 < n && numbArr[i + 1][j] == 0 && !isPreset(num + 1))
		findSol(i + 1, j, num + 1);    
	
	if (!isPreset(numbArr[i][j]))
		numbArr[i][j] = 0;    
}

bool Numbrix::isPreset(int val) 
{
	for (int i = 0; i < presets.size(); i++)
		if (val == presets[i])
			return true;
	return false;
}

void Numbrix::redrawGrid(std::string name)  
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			numbArr[i][j] = cpyArr[i][j];
}

int Numbrix::findFirstNum() 
{
	int i, j = 0, returnVal = 0;
	int temp = numbArr[n - 1][0];
	returnVal = (n - 1) * n + 0;
	for (i = n - 1; i >= 0; i--)
	{
		for (j = 0; j < n; j++)
		{
			if (temp == 0)
				temp = numbArr[i][j];
			else if (numbArr[i][j] != 0 && numbArr[i][j] < temp)
			{
				temp = numbArr[i][j];
				returnVal = i * n + j;
			}
		}
	}
	return returnVal;
}

void Numbrix::print()
{
	cout << '\n';
	drawHLine();
	for (int i = n - 1; i >= 0; i--)
	{
		for (int j = 0; j < n; j++)
		{
			cout << "|";
			if (numbArr[i][j] == 0)
				cout << std::setw(3) << "    ";
			else
				cout << std::setw(3) << numbArr[i][j] << " ";
		}
		cout << "|" << endl;
		drawHLine();
	}
}

void Numbrix::drawHLine()
{
	for (int i = 0; i < n; i++)
		cout << "-----";
	cout << "-";
	cout << endl;
}












