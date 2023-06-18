#include "Board.h"
#include "Definitions.h"
#include <iostream>
#include <thread>
#include <random>

Board::Board(GameDataRef data, GameDifficulty d) : _data(data), diff(d)
{
	saved = false;
	this->Init();
}

void Board::Init()
{
	this->_data->assets.LoadTexture(Square, SQUARE_FILEPATH);

	square.setTexture(this->_data->assets.GetTexture(Square));
	_backButton.setTexture(this->_data->assets.GetTexture(BackButton));

	square.setScale(.5f,.5f);
	_backButton.setScale(.4f, .4f);

	square.setPosition(125,25);
	_backButton.setPosition(0, SCREEN_HEIGHT - (_backButton.getGlobalBounds().height));

	timer.setFont(_data->assets.GetFont(Default));
	timer.setString("00:00");
	timer.setPosition(sf::Vector2f(square.getPosition().x+square.getGlobalBounds().width+ (timer.getGlobalBounds().width/2) - 13, 50));
	timer.setFillColor(sf::Color::Black);

	quitText.setFont(_data->assets.GetFont(Default));
	quitText.setString("");
	quitText.setCharacterSize(20);
	quitText.setFillColor(sf::Color::Black);

	mistakeText.setFont(_data->assets.GetFont(Default));
	mistakeText.setString("");
	mistakeText.setCharacterSize(20);
	mistakeText.setFillColor(sf::Color::Black);
	mistakeText.setPosition(sf::Vector2f(SCREEN_WIDTH - 125, 100));

	mistakes = 0;

	boardInit();
}

void newSudoku(std::string path,bool& b)
{
	Sudoku sudo;
	sudo.Generate(path);
	b = false;
}

void Board::boardInit()
{
	done = false;
	std::random_device rd;
	std::uniform_int_distribution<int> dist(0, 8);
	std::uniform_int_distribution<int> d(25, 65);
	int x, y;	

	switch (diff)
	{
	case Easy:
		if (this->_data->assets.activeThread == false)
		{
			std::thread t1(newSudoku, EASY_SUDOKU_FILEPATH, std::ref(this->_data->assets.activeThread));
			t1.detach();
			this->_data->assets.activeThread = true;
		}
		sudoku = new Sudoku(EASY_SUDOKU_FILEPATH);
		originalSudoku = new Sudoku(EASY_SUDOKU_FILEPATH);
		for (int i = 0; i < 25; i++)
		{
			x = dist(rd);
			y = dist(rd);
			sudoku->getSudoku()[x][y] = 0;
		}
		break;
	case Medium:
		if (this->_data->assets.activeThread == false)
		{
				std::thread t2(newSudoku, MEDIUM_SUDOKU_FILEPATH, std::ref(this->_data->assets.activeThread));
				t2.detach();
				this->_data->assets.activeThread = true;
		}
		sudoku = new Sudoku(MEDIUM_SUDOKU_FILEPATH);
		originalSudoku = new Sudoku(MEDIUM_SUDOKU_FILEPATH);
		for (int i = 0; i < 40; i++)
		{
			x = dist(rd);
			y = dist(rd);
			sudoku->getSudoku()[x][y] = 0;
		}
		break;
	case Hard:
		if (this->_data->assets.activeThread == false)
		{
			std::thread t3(newSudoku, HARD_SUDOKU_FILEPATH, std::ref(this->_data->assets.activeThread));
			t3.detach();
			this->_data->assets.activeThread = true;
		}
		sudoku = new Sudoku(HARD_SUDOKU_FILEPATH);
		originalSudoku = new Sudoku(HARD_SUDOKU_FILEPATH);
		for (int i = 0; i < 50; i++)
		{
			x = dist(rd);
			y = dist(rd);
			sudoku->getSudoku()[x][y] = 0;
		}
		break;
	case Random:
		if (this->_data->assets.activeThread == false)
		{
			std::thread t(newSudoku, RANDOM_SUDOKU_FILEPATH,std::ref(this->_data->assets.activeThread));
			t.detach();
			this->_data->assets.activeThread = true;
		}
		sudoku = new Sudoku(RANDOM_SUDOKU_FILEPATH);
		originalSudoku = new Sudoku(RANDOM_SUDOKU_FILEPATH);

		for (int i = 0; i < d(rd); i++)
		{
			x = dist(rd);
			y = dist(rd);
			sudoku->getSudoku()[x][y] = 0;
		}
		break;
	default:
		//
		break;
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			sf::Vector2f pos = sf::Vector2f(square.getPosition().x + i * square.getGlobalBounds().width / 9, square.getPosition().y + j * square.getGlobalBounds().height / 9);
			sf::Vector2f size = sf::Vector2f(square.getGlobalBounds().width / 9, square.getGlobalBounds().height / 9);
			Tile* tmp = new Tile(pos, size, _data->assets.GetFont(Default));
			tmp->setId(i,j);
			board.push_back(*tmp);
			if (sudoku->getNum(i, j) != std::to_string(0))
			{
				board[9 * i + j].setDigit(sudoku->getNum(i, j),true);
				board[9 * i + j].setOriginal(true);
			}
		}
	}
}

void Board::boardUpdate()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			
			if (board[9 * i + j].isActive())
			{
				if (!board[9 * i + j].isOriginal())
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
					{
						bool t = false;
						if (originalSudoku->getSudoku()[i][j] == 1)
						{
							t = true;
						}
						else { if (sudoku->getSudoku()[i][j] != 1) { mistakes++; } }
						sudoku->getSudoku()[i][j] = 1;
						board[9 * i + j].setDigit(std::to_string(1),t);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
					{
						bool t = false;
						if (originalSudoku->getSudoku()[i][j] == 2)
						{
							t = true;
						}
						else { if (sudoku->getSudoku()[i][j] != 2) { mistakes++; } }
						sudoku->getSudoku()[i][j] = 2;
						board[9 * i + j].setDigit(std::to_string(2), t);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
					{
						bool t = false;
						if (originalSudoku->getSudoku()[i][j] == 3)
						{
							t = true;
						}
						else { if (sudoku->getSudoku()[i][j] != 3) { mistakes++; } }
						sudoku->getSudoku()[i][j] = 3;
						board[9 * i + j].setDigit(std::to_string(3), t);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
					{
						bool t = false;
						if (originalSudoku->getSudoku()[i][j] == 4)
						{
							t = true;
						}
						else { if (sudoku->getSudoku()[i][j] != 4) { mistakes++; } }
						sudoku->getSudoku()[i][j] = 4;
						board[9 * i + j].setDigit(std::to_string(4), t);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
					{
						bool t = false;
						if (originalSudoku->getSudoku()[i][j] == 5)
						{
							t = true;
						}
						else { if (sudoku->getSudoku()[i][j] != 5) { mistakes++; } }
						sudoku->getSudoku()[i][j] = 5;
						board[9 * i + j].setDigit(std::to_string(5), t);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
					{
						bool t = false;
						if (originalSudoku->getSudoku()[i][j] == 6)
						{
							t = true;
						}
						else { if (sudoku->getSudoku()[i][j] != 6) { mistakes++; } }
						sudoku->getSudoku()[i][j] = 6;
						board[9 * i + j].setDigit(std::to_string(6), t);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
					{
						bool t = false;
						if (originalSudoku->getSudoku()[i][j] == 7)
						{
							t = true;
						}
						else { if (sudoku->getSudoku()[i][j] != 7) { mistakes++; } }
						sudoku->getSudoku()[i][j] = 7;
						board[9 * i + j].setDigit(std::to_string(7), t);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
					{
						bool t = false;
						if (originalSudoku->getSudoku()[i][j] == 8)
						{
							t = true;
						}
						else { if (sudoku->getSudoku()[i][j] != 8) { mistakes++; } }
						sudoku->getSudoku()[i][j] = 8;
						board[9 * i + j].setDigit(std::to_string(8), t);
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
					{
						bool t = false;
						if (originalSudoku->getSudoku()[i][j] == 9)
						{
							t = true;
						}
						else { if (sudoku->getSudoku()[i][j] != 9) { mistakes++; } }
						sudoku->getSudoku()[i][j] = 9;
						board[9 * i + j].setDigit(std::to_string(9), t);
					}
				}
			}
		}

	}
	if (_data->input.IsSpriteClicked(square, sf::Mouse::Middle, _data->window))
	{
		for (int i = 0; i < board.size(); i++)
		{
			board[i].setActive(false);
		}
	}
	
	for (int i = 0; i < board.size(); i++)
	{
		if (_data->input.IsRectangleClicked(board[i].getShape(), sf::Mouse::Left, _data->window))
		{
			board[i].setActive(true);
			for (int j = 0; j < board.size(); j++)
			{
				if (j != i)
				{
					board[j].setActive(false);
				}
			}
		}
		if (_data->input.IsRectangleClicked(board[i].getShape(), sf::Mouse::Right, _data->window))
		{
			if (!board[i].isOriginal())
			{
				board[i].setDigit("",true);
				sudoku->getSudoku()[i / 9][i % 9] = 0;
			}
		}
		board[i].Update();
	}
	int min = (int)time.getElapsedTime().asSeconds() / 60;
	int sec = (int)time.getElapsedTime().asSeconds() % 60;
	std::string tmp= "";
	if (min < 10)
	{
		tmp += "0";
	}
	if (sec < 10)
	{
		tmp +=  std::to_string(min) + ":0" + std::to_string(sec);
	}
	else  tmp += std::to_string(min) + ":" + std::to_string(sec);

	timer.setString(tmp);

	score = time.getElapsedTime().asSeconds();
}

void Board::Update()
{
	if (clk.getElapsedTime().asSeconds() > .05f)
	{
		if (_data->input.IsSpriteClicked(_backButton, sf::Mouse::Left, _data->window))
		{
			_data->machine.RemoveState();
		}
		if (!done && mistakes<3)
		{
			boardUpdate();
			clk.restart();
		}
	}
	if (sudoku->operator==(*originalSudoku))
	{
		done = true;
	}
	if (done) // victory screen
	{
		for (int i = 0; i < board.size(); i++)
		{
			for (int j = 0; j < board.size(); j++)
			{
				board[j].setActive(false);
			}
		}
		std::string t = "Sudoku completed. Returning to menu in: " + std::to_string(10 - (int)clk.getElapsedTime().asSeconds()) + " seconds.";
		if ((int)clk.getElapsedTime().asSeconds() == 9)
		{
			t = "Sudoku completed. Returning to menu in: " + std::to_string(10 - (int)clk.getElapsedTime().asSeconds()) + " second.";
		}
		quitText.setString(t);
		quitText.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - quitText.getGlobalBounds().width / 2, SCREEN_HEIGHT - 80));

		if (clk.getElapsedTime().asSeconds() > 10)
		{
			_data->machine.RemoveState();
		}
		if(!saved)
		{
			saved = true;
			save = new Saver(diff,mistakes,score);
		}
	}
	std::string mistake = "Mistakes: " + std::to_string(mistakes);
	mistakeText.setString(mistake);

	if (mistakes >= 3)  // lose screen
	{
		for (int i = 0; i < board.size(); i++)
		{
			for (int j = 0; j < board.size(); j++)
			{
				board[j].setActive(false);
			}
		}
		std::string t = "3 mistakes were made. Returning to menu in: " + std::to_string(10 - (int)clk.getElapsedTime().asSeconds()) + " seconds.";
		if ((int)clk.getElapsedTime().asSeconds() == 9)
		{
			t = "3 mistakes were made. Returning to menu in: " + std::to_string(10 - (int)clk.getElapsedTime().asSeconds()) + " second.";
		}
		quitText.setString(t);
		quitText.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - quitText.getGlobalBounds().width / 2, SCREEN_HEIGHT - 80));

		if (clk.getElapsedTime().asSeconds() > 10)
		{
			_data->machine.RemoveState();
		}
	}
}

void Board::Draw()
{
	_data->window.draw(timer);
	_data->window.draw(square);
	_data->window.draw(quitText);
	_data->window.draw(mistakeText);
	for (int i = 0; i < board.size(); i++)
	{
		if (board[i].isActive() == true)
		{
			_data->window.draw(board[i].getShape());
		}
		_data->window.draw(board[i].getText());
	}
	_data->window.draw(_backButton);
}

