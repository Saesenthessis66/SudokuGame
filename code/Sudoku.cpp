#include "Sudoku.h"
#include <fstream>
#include <string>
#include <regex>

#include "Definitions.h"

void Sudoku::print()
{
    std::cout << std::endl;
    for (int i = 0; i < 9; i++)
    {
        std::cout << "\t";
        for (int j = 0; j < 9; j++)
        {
            std::cout << sudoku[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Sudoku::init()
{
	for (int i = 0; i < 9; i++)
	{
		tmp.push_back(0);
	}
}

void Sudoku::fillSquare(int x, int y)
{
    std::vector<int> nums;
    std::random_device rd;
    for (int x = 1; x <= 9; x++)
    {
        nums.push_back(x);
    }

    for (int i = 0 + x; i < 3 + x; i++)
    {
        for (int j = 0 + y; j < 3 + y; j++)
        {
            if (nums.size() != 0)
            {
                std::uniform_int_distribution<int> dist(0, nums.size() - 1);
                int tmp = dist(rd);
                sudoku[i][j] = nums[tmp];
                nums.erase(nums.begin() + tmp);
            }
        }
    }
}

Sudoku::Sudoku(std::string path) 
{
    std::ifstream ifile(path);

    const std::regex pattern("[1-9]{9}");

    if (ifile.is_open())
    {
        std::string str;
        while (getline(ifile, str))
        {
            std::vector<int> tmp;
            tmp.clear();
            while (std::ranges::find(str, ' ') != std::ranges::end(str))
                str.erase(std::ranges::find(str, ' '));
            
            if (std::regex_match(str, pattern))
            {
                for (int i = 0; i < 9; i++)
                {
                    tmp.push_back(str[i] - 48);
                }
                sudoku.push_back(tmp);
            }
            else std::cout << "WRONG SUDOKU FORMAT ON FILE: " << path << std::endl;
        }
    }
    else
    {
        std::cout << "Could not load sudoku from " << path << std::endl;
    }
}

Sudoku::Sudoku()
{
    int iters = 0;  

    for (int i = 0; i < 9; i++)
    {
        tmp.push_back(0);
    }

    do
    {
       // std::cout << "\n      STARTING NEW ITERATION";
        sudoku.clear();
        for (int i = 0; i < 9; i++)
        {
            sudoku.push_back(tmp);
        }

        fillSquare(0, 0);
        fillSquare(3, 3);
        fillSquare(6, 6);

     //   std::cout << std::endl;
     //   print();

        done = fillSudoku();
        iters++;

    } while (!done);

   // print();
  //  std::cout << iters;
}

int Sudoku::fillSudoku()
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(1, 9);

    int count = 0;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (sudoku[i][j] == 0)
            {
                int tmp = dist(rd);
                while (!good(tmp, i, j))
                {
                    if (count > 1000)
                    {
                        return 0;
                    }
                    else
                    {
                        tmp = dist(rd);
                        count++;
                    }
                }
                sudoku[i][j] = tmp;
             //  print();
            }
        }
    }
    return 1;
}

bool Sudoku::good(int num, int row, int column)
{
    int _row = row / 3 * 3;
    int _column = column / 3 * 3;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (num == sudoku[_row + i][_column + j])
            {
                return false;
            }
        }
    }

    for (int i = 0; i < 9; i++)
    {
        if (num == sudoku[row][i])
        {
            return false;
        }

        if (num == sudoku[i][column])
        {
            return false;
        }

    }
    return true;
}

void Sudoku::Generate(std::string path)
{
    std::ofstream ofile(path);
    for (int i = 0; i < 9; i++)
    {
        for(int j=0;j<9;j++)
        {
            ofile << sudoku[i][j] << " ";
        }
        ofile<< std::endl;
    }

}

std::string Sudoku::getNum(int row, int column)
{
    return std::to_string(sudoku[row][column]);
}

std::vector<std::vector<int>>& Sudoku::getSudoku()
{
    return sudoku;
}

Sudoku& Sudoku::operator=(const Sudoku& sudo)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            this->sudoku[i][j] = sudo.sudoku[i][j];
        }
    }
    return *this;
}

bool Sudoku::operator==(const Sudoku& sudo)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (this->sudoku[i][j] != sudo.sudoku[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

Sudoku::Sudoku(const Sudoku& sudo)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            this->sudoku[i][j] = sudo.sudoku[i][j];
        }
    }
}
