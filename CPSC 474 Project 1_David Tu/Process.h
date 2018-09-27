#pragma once
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Process{
public:
	Process(const string row[], const int cols, const string name);
	~Process();

	void print();
	void printSolution();
	
	void calculateLamport();

private:
	int noEvents;
	string pName;
	//Pointers to arrays
	string *events;
	int *output;
};

