#pragma once
#include<iostream>
#include<string>
#include <fstream>

class Printer{
private:
	int ROWS;
	int COLS;

public:
	Printer(const int rows, const int cols);
	virtual ~Printer();

	void printIntArr(const int array[], const int size, const std::string name);
	
	void printIntMat(const int mat[5][25], const std::string name);
	void printIntMatrix(int **mat, const std::string name, const int rows, const int cols);
	
	void printStrMat(const std::string mat[5][25], const std::string name);
	void printStringMatrix(std::string **mat, const std::string name, const int rows, const int cols);
	
	void toFile(const std::string mat[5][25], const std::string name, const bool result);
	void toFile(const int mat[5][25], const std::string name);
};

