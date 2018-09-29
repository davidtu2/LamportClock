// CPSC 474 Project 1_David Tu.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

#include "pch.h"
#include <iostream>
#include <string>
#include <algorithm>

//Globals
//Indicates the number of Processes
const int ROWS = 5;
//Indicates the number of Events
const int COLS = 24;
bool requestIn = false;

//The test matrix will allocate space for testing
std::string test[ROWS][COLS] = {"NULL"};

//The output matrix will contain all of the LC values
int output[ROWS][COLS] = {0};

//The sendEvents array will contain all of the send event values, in their corresponding positions
//For instance, for s1 = 10, 10 will be stored in sendEvents[0]
int sendEvents[COLS];

//Prototypes
void printIntArr(const int array[], const int size, const std::string name);
void printStringMatrix(std::string **mat, const std::string name, const int rows, const int cols);

//These are dependant on the globals: ROWS and COLS
void printIntMat(const int mat[ROWS][COLS], const std::string name);
void printStrMat(const std::string mat[ROWS][COLS], const std::string name);
void calculateLamport(const std::string row[ROWS][COLS], const int rowNo);
void prepTest(std::string **mat, const std::string testName, const int rows, const int cols);

int main(){
	//Variables will to hold user input, or they can just be hardcoded here:
	std::string name = "Test 1";
	int rows = 3;
	int cols = 4;

	//Unit Test(s):
	std::string test1[3][4] = {
		{"a", "s1","r3", "b"},
		{"c", "r2", "s3", "NULL"},
		{"r1", "d", "s2", "e"}
	};

	std::string test2[3][4] = {
		{"s1", "b", "r3", "e"},
		{"a", "r2", "s3", "NULL"},
		{"r1", "c", "d", "s2"}
	};

	//Request user input:
	if (requestIn) {
		std::cout << "What is the name of your matrix? ";
		std::cin >> name;
		std::cout << "Enter the number of rows:";
		std::cin >> rows;
		std::cout << "Enter the number of cols:";
		std::cin >> cols;
		std::cout << std::endl;
	}

	//Normal arrays don't support variable sizes, so I need to allocate it in the heap
	//Create a pointer that will point to another pointer that points to strings (the 'string **' expression)
	//The pointer that points to strings will be a set of string pointers of size, r
	//(Think of it as declaring an array of string pointers: 'new string*[r]')
	std::string **test_1 = new std::string*[rows];

	//For each row, allocate the number of columns (i.e. the number of entries)
	for (int i = 0; i < rows; i++) {
		test_1[i] = new std::string[cols];
	}

	//Initialize the newly allocated matrix with NULL strings
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			test_1[i][j] = "NULL";
		}
	}

	printStringMatrix(test_1, "Initialized " + name + "[" + std::to_string(rows) + "][" + std::to_string(cols) + "]", rows, cols);

	if (requestIn) {
		//Have the user to populate the matrix
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				std::cout << "Enter entry for " << name << "[" << i << "][" << j << "]:";
				std::cin >> test_1[i][j];
			}
		}

		std::cout << std::endl;
	}
	
	else{
		//Transfer the array into the allocated one
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				test_1[i][j] = test1[i][j];
			}
		}
	}

	printStringMatrix(test_1, "This is your input matrix, " + name + "[" + std::to_string(rows) + "][" + std::to_string(cols) + "]", rows, cols);
	
	prepTest(test_1, "Test Case 1", rows, cols);

	std::cout << "Calculating LC values:" << std::endl;
	calculateLamport(test, 0);
	printIntArr(sendEvents, COLS, "Populated sendEvents array");
	printIntMat(output, "Test Case 1 Results");

	//Make sure to deallocate
	//Delete the column arrays that's within each row
	for (int i = 0; i < rows; i++) {
		delete[] test_1[i];
	}

	//Then delete the row array itself
	delete[] test_1;

	return 0;
}

void printIntMat(const int mat[ROWS][COLS], const std::string name) {
	std::cout << name << ":" << std::endl;

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (j == COLS - 1) {
				std::cout << mat[i][j] << std::endl;
			}
			else {
				std::cout << mat[i][j] << ", ";
			}
		}
	}

	std::cout << std::endl;
}

void printStrMat(const std::string mat[ROWS][COLS], const std::string name) {
	std::cout << name << ":" << std::endl;

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (j == COLS - 1) {
				std::cout << mat[i][j] << std::endl;
			}
			else {
				std::cout << mat[i][j] << ", ";
			}
		}
	}

	std::cout << std::endl;
}

void printStringMatrix(std::string **mat, const std::string name, const int rows, const int cols) {
	std::cout << name << ":" << std::endl;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (j == cols - 1) {
				std::cout << mat[i][j] << std::endl;
			}
			else {
				std::cout << mat[i][j] << ", ";
			}
		}
	}

	std::cout << std::endl;
}

void printIntArr(const int array[], const int size, const std::string name) {
	std::cout << name << ":" << std::endl;

	for (int i = 0; i < size; i++) {
		if (i == size - 1) {
			std::cout << array[i] << std::endl;
		}
		else {
			std::cout << array[i] << ", ";
		}
	}

	std::cout << std::endl;
}

void calculateLamport(const std::string mat[ROWS][COLS], const int rowNo) {
	std::cout << "Processing p" << rowNo << ":" << std::endl;

	for (int i = 0; i < COLS; i++) {
		//Ignore all entries with the 'NULL' string
		if (mat[rowNo][i] != "NULL") {

			//CASE 1: Internal events
			if (mat[rowNo][i].at(0) != 's' && mat[rowNo][i].at(0) != 'r') {
				std::cout << "Processing internal event: " << mat[rowNo][i] << std::endl;

				//Internal event value is 1, so just add it to the prev LC value, K: K + 1
				//If this is the first event, then there's no prev LC value, so make K = 0. Thus, K + 1 =  1:
				if (i == 0) {
					output[rowNo][i] = 1;
				}

				else {
					output[rowNo][i] = output[rowNo][i - 1] + 1;
				}
			}

			//CASE 2: Send events
			else if (mat[rowNo][i].at(0) == 's') {
				std::cout << "Processing send event: " << mat[rowNo][i] << std::endl;

				//Send event value is 1, so just add it to the prev LC value, K: K + 1
				//If this is the first event, then there's no prev LC value, so make K = 0. Thus, K + 1 =  1:
				if (i == 0) {
					output[rowNo][i] = 1;
				}

				else {
					output[rowNo][i] = output[rowNo][i - 1] + 1;
				}

				//Update sendEvents array with the value into the corresponding element position
				//Note that a char is actually a number interpreted through the ASCII table
				//By looking at the table, you can find that '0' is 48, '1' 49 and so on until '9' as 57
				int eventNo = mat[rowNo][i].at(1) - 48;
				sendEvents[eventNo - 1] = output[rowNo][i];
			}

			//Case 3: Receive event
			else if (mat[rowNo][i].at(0) == 'r') {
				std::cout << "Processing receive event: " << mat[rowNo][i] << std::endl;

				//Receive event value is determined by max(K, sendVal) + 1,
				//where K is the prev LC value and sendVal is the value of the corresponding send event
				//To perform this calculation, we first need the values of K and sendVal:
				int k;

				//If this is the first event, then there's no prev LC value, so make K = 0. Thus, K + 1 =  1:
				if (i == 0) {
					k = 0;
				}

				else {
					k = output[rowNo][i - 1];
				}

				std::cout << "The prev LC value, K, is: " << k << std::endl;

				//Now that we have K, obtain sendVal:

				//Grab the event number
				//Note that a char is actually a number interpreted through the ASCII table
				//By looking at the table, you can find that '0' is 48, '1' 49 and so on until '9' as 57
				int eventNo = mat[rowNo][i].at(1) - 48;

				//Grab the sendVal by querying from the sendEvents array
				int sendVal = sendEvents[eventNo - 1];

				std::cout << "Queried sendVal value is: " << sendVal << std::endl;

				//Finally calculate LC value:
				if (sendVal > 0) {
					output[rowNo][i] = std::max(k, sendVal) + 1;
				}

				else if (sendVal < 0) {
					std::cout << std::endl;

					//Calculate the LC values of the other processes so that the sendEvents array will be fully populated
					calculateLamport(mat, rowNo + 1);

					std::cout << "Resume processing receive event: " << mat[rowNo][i] << std::endl;

					//Now, re-query the sendVal and determine the value
					sendVal = sendEvents[eventNo - 1];
					std::cout << "Updated sendVal value is: " << sendVal << std::endl;
					std::cout << "The prev LC value, K, is: " << k << std::endl;
					output[rowNo][i] = std::max(k, sendVal) + 1;
				}

				else {
					std::cout << "An error occured in the LC value calculation: SendVal = 0" << std::endl;
				}
			}

			else {
				std::cout << "An error occured in the LC value calculation" << std::endl;
			}

			std::cout << "Result: " << output[rowNo][i] << std::endl;
		}
	}

	std::cout << std::endl;
}

void prepTest(std::string **mat, const std::string testName, const int rows, const int cols) {
	//Initialize the test space
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			test[i][j] = "NULL";
		}
	}

	printStrMat(test, "Initialized test space");

	//To avoid out of bounds errors, transfer the given matrix to a bigger one
	//In this method, we are passing a pointer to a matrix as if it was a 1D array
	//This is possible since 2D arrays are stored in memory same was as a 1D array (One long line of memory)
	//That is why k is used as an incrementor to access the positions of the matrix
	int k = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			//test[i][j] = mat[k];
			test[i][j] = mat[i][j];
			k++;
		}
	}

	printStrMat(test, testName);

	//Initialize all output to 0
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			output[i][j] = 0;
		}
	}

	printIntMat(output, "Initialized output");

	//Initialize sendEvents array to -1
	for (int i = 0; i < COLS; i++) {
		sendEvents[i] = -1;
	}

	printIntArr(sendEvents, COLS, "Initialized sendEvents array");
}