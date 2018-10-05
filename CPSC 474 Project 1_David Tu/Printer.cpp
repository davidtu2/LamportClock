#include "pch.h"
#include "Printer.h"

Printer::Printer(const int rows, const int cols){
	ROWS = rows;
	COLS = cols;
}

Printer::~Printer(){

}

void Printer::printIntMatrix(int **mat, const std::string name, const int rows, const int cols) {
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

void Printer::printIntArr(const int array[], const int size, const std::string name) {
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

void Printer::printIntMat(const int mat[5][25], const std::string name) {
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

void Printer::printStrMat(const std::string mat[5][25], const std::string name) {
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

void Printer::toFile(const std::string mat[5][25], const std::string name, const bool result) {
	std::ofstream myFile;
	myFile.open("myFile.txt");

	myFile << name << ":\n";

	if (result == true) {
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				if (j == COLS - 1) {
					myFile << mat[i][j] << "\n";
				}

				else {
					myFile << mat[i][j] << ", ";
				}
			}
		}
	}

	else {
		myFile << "INCORRECT";
	}

	myFile << "\n";
	myFile.close();
}

void Printer::printStringMatrix(std::string **mat, const std::string name, const int rows, const int cols) {
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

void Printer::toFile(const int mat[5][25], const std::string name) {
	std::ofstream myFile;
	myFile.open("myFile.txt");

	myFile << name << ":\n";

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (j == COLS - 1) {
				myFile << mat[i][j] << "\n";
			}

			else {
				myFile << mat[i][j] << ", ";
			}
		}
	}

	myFile << "\n";
	myFile.close();
}