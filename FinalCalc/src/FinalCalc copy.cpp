//============================================================================
// Name        : FinalCalc.cpp
// Author      : Glenn Roles
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	//weighted variable
	double weighted;

	//grade wanted
	double wanted;

	//current grade
	double current;

	cout << "What is your current grade?" << endl;
	cin >> current;

	cout << "What is the grade you want?" << endl;
	cin >> wanted;

	cout << "What is the weight of the final?" << endl;
	cin >> weighted;

	//
	// ( required grade - (100% - w)×current grade ) / w
	double nw = weighted/100;
	double final = ((wanted - ((1-nw) * current))/nw);

	cout << setprecision(2) << fixed;

	cout << "You need a " << final << " to get a " << wanted << ".";

	return 0;
}
