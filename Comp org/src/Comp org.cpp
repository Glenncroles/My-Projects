//============================================================================
// Name        : Comp.cpp
// Author      : Glenn Roles
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Hex
{
protected:
	int num;
public:
	Hex(int num);
	void DtoH(int n);
	void rem(int n);
};


Hex :: Hex(int num)
{
	this->num = num;
}

void Hex :: DtoH(int n)
{
	int r = n/16;

	//if our number is less than 16 then print it out in hexadecimal
	if(r == 0)
	{
		//calls the remainder on n
		rem(n);
	}
	else
	{
		//calls the DtoH recursivly on the full number after divding by 16
		DtoH(r);

		//prints each position and puts a number or letter when needed
		rem(n%16);
	}
}

void Hex :: rem(int n)
{
	//write this a function of sorts
	int p1 = n%16;

	//if our remainder is greater than 9 then make it the appropriate number
	if(p1 > 9)
	{
		p1 = p1-9;
		if(p1 == 1)
		{
			cout << "A";
		}
		if(p1 == 2)
		{
			cout << "B";
		}
		if(p1 == 3)
		{
			cout << "C";
		}
		if(p1 == 4)
		{
			cout << "D";
		}
		if(p1 == 5)
		{
			cout << "E";
		}
		if(p1 == 6)
		{
			cout << "F";
		}
	}

	//if not just print our number
	else
	{
		cout << n;
	}
}

int main() {
	//This is just for my main
	cout << "Decimal number: ";
	int n;
	cin >> n;

	//This is the code to be changed into assembly
	cout << "The number in Hexadecimal: ";
	Hex* num = new Hex(n);
	(*num).DtoH(n);


	return 0;
}
