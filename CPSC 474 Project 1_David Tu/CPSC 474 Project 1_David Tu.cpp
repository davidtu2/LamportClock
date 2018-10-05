// CPSC 474 Project 1_David Tu.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <algorithm>
#include "Printer.h"

//Globals
//Indicates the number of Processes
const int ROWS = 5;
//Indicates the number of Events
const int COLS = 25;
//Indicates whether or not the program should accept user input
bool requestIn = false;
Printer printer(ROWS, COLS);

//The test matrix will allocate space for testing
std::string test[ROWS][COLS] = {"NULL"};

//The output matrix will contain all of the LC values, initialized to zero
int output[ROWS][COLS] = {0};

//The sendEvents array will contain all of the send event values, in their corresponding positions
//For instance, for s1 = 10, 10 will be stored in sendEvents[0]
int sendEvents[COLS];

//Prototypes
//These are dependant on the globals: ROWS and COLS
void calculate(const std::string mat[ROWS][COLS], const int start);
void prepTest(std::string **mat, const std::string testName, const int rows, const int cols);

int main(){
	//Variables that will to hold user input:
	std::string name = "Test 1";
	int rows = ROWS;
	int cols = COLS;

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

	std::string test3[3][4] = {
		{"a", "r1", "c", "d"},
		{"e", "f", "g", "h"},
		{"i", "s1", "k", "l"}
	};

	rows = 3;
	cols = 4;

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

	printer.printStringMatrix(test_1, "Initialized " + name + "[" + std::to_string(rows) + "][" + std::to_string(cols) + "]", rows, cols);

	//Have the user to populate the matrix
	if (requestIn) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				std::cout << "Enter entry for " << name << "[" << i << "][" << j << "]:";
				std::cin >> test_1[i][j];
			}
		}

		std::cout << std::endl;
	}

	//Transfer the array into the allocated one
	else{
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				test_1[i][j] = test3[i][j];
			}
		}
	}

	printer.printStringMatrix(test_1, "This is your input matrix, " + name + "[" + std::to_string(rows) + "][" + std::to_string(cols) + "]", rows, cols);
	
	prepTest(test_1, name + " Test Case", rows, cols);

	std::cout << "Calculating LC values:" << std::endl;
	calculate(test, 0);
	printer.printIntArr(sendEvents, COLS, "Populated sendEvents array");
	printer.printIntMat(output, name + " Test Case Results");

	//Make sure to deallocate
	//Delete the column arrays that's within each row
	for (int i = 0; i < rows; i++) {
		delete[] test_1[i];
	}

	//Then delete the row array itself
	delete[] test_1;

	printer.toFile(output, name + " Test Case Results");
	return 0;
}

void calculate(const std::string mat[ROWS][COLS], const int start) {
	std::cout << "Processing p" << start << ":" << std::endl;

	//int i will vary depending on what row we want to calculate
	for (int i = start; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			
			//Ignore all rows which have been already processed
			if (output[i][j] != 0) {
				break;
			}

			//Ignore all entries with the 'NULL' string
			if (mat[i][j] == "NULL") {
				break;
			}

			//CASE 1: Internal events
			if (mat[i][j].at(0) != 's' && mat[i][j].at(0) != 'r') {
				std::cout << "Processing internal event: " << mat[i][j] << std::endl;

				//Internal event value is 1, so just add it to the prev LC value, K: K + 1
				//If this is the first event, then there's no prev LC value, so make K = 0. Thus, K + 1 =  1:
				if (j == 0) {
					output[i][j] = 1;
				}

				else {
					output[i][j] = output[i][j - 1] + 1;
				}
			}

			//CASE 2: Send events
			else if (mat[i][j].at(0) == 's') {
				std::cout << "Processing send event: " << mat[i][j] << std::endl;

				//Send event value is 1, so just add it to the prev LC value, K: K + 1
				//If this is the first event, then there's no prev LC value, so make K = 0. Thus, K + 1 =  1:
				if (j == 0) {
					output[i][j] = 1;
				}

				else {
					output[i][j] = output[i][j - 1] + 1;
				}

				//Update sendEvents array with the value into the corresponding element position
				//stoi is only able to identify ints from strings with dilimeters. That is why substr is used
				int eventNo = stoi(mat[i][j].substr(1, 2));
				sendEvents[eventNo - 1] = output[i][j];
			}

			//Case 3: Receive event
			else if (mat[i][j].at(0) == 'r') {
				std::cout << "Processing receive event: " << mat[i][j] << std::endl;

				//Receive event value is determined by max(K, sendVal) + 1,
				//where K is the prev LC value and sendVal is the value of the corresponding send event
				//To perform this calculation, we first need the values of K and sendVal:
				int k;

				//If this is the first event, then there's no prev LC value, so make K = 0. Thus, K + 1 =  1:
				if (j == 0) {
					k = 0;
				}

				else {
					k = output[i][j - 1];
				}

				std::cout << "The prev LC value, K, is: " << k << std::endl;

				//Now that we have K, obtain sendVal:

				//Grab the event number
				//stoi is only able to identify ints from strings with dilimeters. That is why substr is used
				int eventNo = stoi(mat[i][j].substr(1, 2));

				//Grab the sendVal by querying from the sendEvents array
				int sendVal = sendEvents[eventNo - 1];

				std::cout << "Queried sendVal value is: " << sendVal << std::endl;

				//Finally calculate LC value:
				if (sendVal > 0) {
					output[i][j] = std::max(k, sendVal) + 1;
				}

				else if (sendVal < 0) {
					std::cout << std::endl;

					//Calculate the LC values of the other processes so that the sendEvents array will be fully populated
					calculate(mat, start + 1);

					std::cout << "Resume processing receive event, " << mat[i][j] << ", from P" << start << ":" << std::endl;

					//Now, re-query the sendVal and determine the value
					sendVal = sendEvents[eventNo - 1];
					std::cout << "Updated sendVal value is: " << sendVal << std::endl;
					std::cout << "The prev LC value, K, is: " << k << std::endl;
					output[i][j] = std::max(k, sendVal) + 1;
				}

				else {
					std::cout << "An error occured in the LC value calculation: SendVal = 0" << std::endl;
				}
			}

			else {
				std::cout << "An error occured in the LC value calculation" << std::endl;
			}

			std::cout << "Result: " << output[i][j] << std::endl;
			
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

	printer.printStrMat(test, "Initialized test space");

	//To avoid out of bounds errors, transfer the given matrix to a bigger one
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			test[i][j] = mat[i][j];
		}
	}

	printer.printStrMat(test, testName);

	//Initialize all output to 0
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			output[i][j] = 0;
		}
	}

	printer.printIntMat(output, "Initialized output");

	//Initialize sendEvents array to -1
	for (int i = 0; i < COLS; i++) {
		sendEvents[i] = -1;
	}

	printer.printIntArr(sendEvents, COLS, "Initialized sendEvents array");
}