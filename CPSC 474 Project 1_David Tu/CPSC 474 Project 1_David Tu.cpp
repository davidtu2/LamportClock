// CPSC 474 Project 1_David Tu.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

#include "pch.h"
#include <iostream>
#include <string>
#include <algorithm>

//Globals
//Indicates the number of Processes:
const int ROWS = 3;
//Indicates the number of Events:
const int COLS = 4;

//The output matrix will contain all of the LC values
//We will initialize this matrix to 0
int output[ROWS][COLS] = { 0 };

//The sendEvents array will contain all of the send event values, in their corresponding positions
//For instance, for s1 = 10, 10 will be stored in sendEvents[0]
int sendEvents[COLS];

std::string test[ROWS][COLS] = {
	{"a", "s1","r3", "b"},
	{"c", "r2", "s3", "NULL"},
	{"r1", "d", "s2", "e"}
};

std::string test2[ROWS][COLS] = {
	{"s1", "b", "r3", "e"},
	{"a", "r2", "s3", "NULL"},
	{"r1", "c", "d", "s2"}
};

//Prototypes
void printIntArr(int array[], int size, std::string name);

//These are dependant on the global variables: ROWS, COLS, and test2
void printIntMat(int mat[ROWS][COLS], std::string name);
void printStrMat(std::string mat[ROWS][COLS], std::string name);
void calculateLamport(const std::string row[], const int rowNo, const int cols);

int main(){
	//Test:
	printStrMat(test2, "Test Case 1");

	//Setup and initialization:
	printIntMat(output, "Initialized output");

	//Initialize sendEvents array to -1
	for (int i = 0; i < COLS; i++) {
		sendEvents[i] = -1;
	}

	printIntArr(sendEvents, COLS, "Initialized sendEvents array");

	//Calculate LC values:
	std::cout << "Calculating LC values:" << std::endl;
	calculateLamport(test2[0], 0, COLS);
	printIntArr(sendEvents, COLS, "Populated sendEvents array");
	printIntMat(output, "Test Case 1 Results");

	return 0;
}

void printIntMat(int mat[ROWS][COLS], std::string name) {
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

void printStrMat(std::string mat[ROWS][COLS], std::string name) {
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

void printIntArr(int array[], int size, std::string name) {
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

void calculateLamport(const std::string row[], const int rowNo, const int cols) {
	std::cout << "Processing p" << rowNo << ":" << std::endl;

	for (int i = 0; i < cols; i++) {
		//Ignore all entries with the 'NULL' string
		if (row[i] != "NULL") {

			//CASE 1: Internal events
			if (row[i].at(0) != 's' && row[i].at(0) != 'r') {
				std::cout << "Processing internal event: " << row[i] << std::endl;

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
			else if (row[i].at(0) == 's') {
				std::cout << "Processing send event: " << row[i] << std::endl;

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
				int eventNo = row[i].at(1) - 48;
				sendEvents[eventNo - 1] = output[rowNo][i];
			}

			//Case 3: Receive event
			else if (row[i].at(0) == 'r') {
				std::cout << "Processing receive event: " << row[i] << std::endl;

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
				int eventNo = row[i].at(1) - 48;

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
					calculateLamport(test2[rowNo + 1], rowNo + 1, cols);

					std::cout << "Resume processing receive event: " << row[i] << std::endl;

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