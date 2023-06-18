#pragma once

#include<SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <ranges>
#include <Windows.h>
#include<vector>
import helper;

class Sudoku
{
	std::vector < std::vector<int>> sudoku;
	std::vector<int> tmp;
	bool done;
	
	void init();
	void fillSquare(int x, int y);

public:

	Sudoku(std::string path);
	Sudoku();
	void print();
	int fillSudoku();

	bool good(int num, int row, int column);

	void Generate(std::string path);

	std::string getNum(int row, int column);
	std::vector < std::vector<int>>& getSudoku();

	Sudoku& operator = (const Sudoku& sudo);
	bool operator ==(const Sudoku&);
	Sudoku(const Sudoku& sudo);
};

