#include "pch.h"
#include "Process.h"

Process::Process(string row[], int cols, string name){
	pName = name;
	noEvents = cols;

	//Now that we know the number of events for this process, specify the size of the arrays
	events = new string[noEvents];
	output = new int[noEvents];

	//Initialize all of the arrays to "zero"
	for (int i = 0; i < noEvents; i++) {
		events[i] = "0";
		output[i] = 0;
	}

	//Copy the given matrix row into the events array
	for (int i = 0; i < noEvents; i++) {
		if (row[i] != "NULL") {
			//We only want valid entries
			events[i] = row[i];
		}
	}
}

Process::~Process(){
	delete[] events;
	delete[] output;
}

void Process::print() {
	cout << "The events for process " << pName << " are as follows:" << endl;

	for (int i = 0; i < noEvents; i++) {
		//If I'm on the last entry, don't bother putting a "," at the end
		if (i == noEvents - 1) {
			cout << events[i];
		}
		else {
			cout << events[i] << ", ";
		}
	}

	cout << endl;
}

void Process::printSolution() {
	cout << "The LC values for process " << pName << " are as follows:" << endl;
	
	for (int i = 0; i < noEvents; i++) {
		if (i == noEvents - 1) {
			cout << output[i];
		}
		else {
			cout << output[i] << ", ";
		}
	}
	
	cout << endl;
}