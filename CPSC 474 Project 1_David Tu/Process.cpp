#include "pch.h"
#include "Process.h"

Process::Process(const string row[], const int cols, const string name){
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
	cout << "The events for process " << pName << " are:" << endl;

	for (int i = 0; i < noEvents; i++) {
		//If I'm on the last entry, don't bother putting a "," at the end
		if (i == noEvents - 1) {
			cout << events[i];
		}
		else {
			cout << events[i] << ", ";
		}
	}

	cout << "\n" << endl;
}

void Process::printSolution() {
	cout << "The LC values for process " << pName << " are:" << endl;
	
	for (int i = 0; i < noEvents; i++) {
		if (i == noEvents - 1) {
			cout << output[i];
		}
		else {
			cout << output[i] << ", ";
		}
	}
	
	cout << "\n" << endl;
}

void Process::calculateLamport() {
	for (int i = 0; i < noEvents; i++) {

		//CASE 1: Internal events:
		if (events[i].at(0) != 'r' && events[i].at(0) != 's') {
			cout << "Processing internal event: " << events[i] << endl;
			
			//Internal event value is 1, so just add it to the prev LC value, K: K + 1
			//If this is the first event, then there's no prev LC value, so make K = 0:
			if (i == 0) {
				output[i] = 1;
			}
			else {
				output[i] = output[i - 1] + 1;
			}
		}

		//CASE 2: Send events
		else if (events[i].at(0) == 's') {
			cout << "Processing send event: " << events[i] << endl;

			//Send event value is 1, so just add to prev LC value, K: K + 1
			//If this is the first event, then there's no prev LC value, so make K = 0:
			if (i == 0) {
				output[i] = 1;
			}
			else {
				output[i] = output[i - 1] + 1;
			}
		}

		//CASE 3: Receive events
		else if (events[i].at(0) == 'r') {	
			cout << "Processing receive event: " << events[i] << endl;

			//Receive event value is determined by max(K, sendVal) + 1,
			//where K is the prev LC value and sendVal is the value of the corresponding send event
			//To perform this calculation, we first need the values of K and sendVal:
			
			//Obtain K:
			int k;
			
			//If this is the first event, then there's no prev LC value, so make K = 0:
			if (i == 0) {
				k = 0;
			}
			else {
				k = output[i - 1];
			}

			cout << "The prev LC value, K, is: " << k << endl;

			//Now that we have K, obtain sendVal:
			int sendVal;//TODO: get this from a shared variable
			sendVal = 10;

			cout << "Obtained sendVal value is: " << sendVal << endl;

			//Finally calculate LC value:
			output[i] = max(k, sendVal) + 1;
		}
		
		else {
			cout << "ERROR in calculateLamport()" << endl;
		}

		cout << "Result: " << output[i] << "\n" << endl;
	}
}