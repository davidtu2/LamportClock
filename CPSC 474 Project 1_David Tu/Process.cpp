#include "pch.h"
#include "Process.h"

Process::Process(string row[], int cols){
	noEvents = cols;

	//Now that we know the number of events for this process, specify the size of the array
	events = new string[noEvents];

	for (int i = 0; i < noEvents; i++) {
		if (row[i] != "NULL") {
			events[i] = row[i];
		}
		else {
			//Replace "NULL" entries with "0"
			events[i] = "0";
		}
		
	}
}

Process::~Process(){
	delete[] events;
}

void Process::print() {
	for (int i = 0; i < noEvents; i++) {
		cout << "THE EVENT IS: " << events[i] << endl;
	}
}
