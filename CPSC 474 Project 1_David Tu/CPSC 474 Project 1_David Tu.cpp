// CPSC 474 Project 1_David Tu.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#include "pch.h"
#include <iostream>
#include <string>
#include "Process.h"
using namespace std;

//Number of Processes:
const int ROWS = 3;
//Number of Events:
const int COLS = 4;

//Prototypes
void printMatrix(string[ROWS][COLS]);

int main(){
	//Unit tests
	//3 rows, 4 columns
	//For simplicity, I will be omitting the use of pointers
	string test[ROWS][COLS] = {
		{"a", "s1","r3", "b"},
		{"c", "r2", "s3", "NULL"},
		{"r1", "d", "s2", "e"}
	};

	Process p0(test[0], COLS, "p0");
	p0.print();
	p0.printSolution();

	Process p1(test[1], COLS, "p1");
	p1.print();
	p1.printSolution();

	Process p2(test[2], COLS, "p2");
	p2.print();
	p2.printSolution();

	//printMatrix(test);

	return 0;
}

void printMatrix(string input[ROWS][COLS]) {
	//First, let's initialize the output matrix that will be printed out so that any entry that is NULL will print out "0" instead
	string output[ROWS][COLS];

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			output[i][j] = "0";
		}
	}

	//Then, copy the input matrix into the the output matrix
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (input[i][j] != "NULL") {
				output[i][j] = input[i][j];
			}
		}
	}


	//Now let's print out the results
	for (int i = 0; i < ROWS; i++) {
		cout << "Process " << i << ":\n";

		for (int j = 0; j < COLS; j++) {
			cout << " Event " << j << " is: " << output[i][j] << endl;
		}
	}
}
