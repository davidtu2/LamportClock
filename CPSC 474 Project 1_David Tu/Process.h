#pragma once
#include <iostream>
#include <string>
using namespace std;

class Process{
public:
	Process(string row[], int cols, string name);
	~Process();

	void print();
	void printSolution();

private:
	int noEvents;
	string pName;
	//Pointers to arrays
	string *events;
	int *output;
};

