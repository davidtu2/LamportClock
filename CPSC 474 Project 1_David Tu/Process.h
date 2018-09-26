#pragma once
#include <iostream>
#include <string>
using namespace std;

class Process{
public:
	Process(string row[], int cols);
	~Process();

	void print();

private:
	int noEvents;
	string *events;//Pointer
};

