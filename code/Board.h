#pragma once

#include "Definitions.h"
#include <SFML/Graphics.hpp>
#include "GameData.h"
#include <vector>
#include "Sudoku.h"
#include "Tile.h"
#include "Saver.h"

import helper;

class Board
{

	GameDataRef _data;

	std::vector <Tile> board;

	std::vector<sf::Text> digits;

	sf::Text timer;
	sf::Text mistakeText;
	sf::Text quitText;

	sf::Sprite square;
	sf::Sprite _backButton;

	Sudoku* sudoku;
	Sudoku* originalSudoku;

	bool done;

	GameDifficulty diff;

	sf::Clock clk;
	sf::Clock time;
	sf::Clock mistake_clk;

	int mistakes;
	int score;

	Saver* save;
	bool saved;

	void boardInit();
	void boardUpdate();

public:
	Board() {}
	Board(GameDataRef data, GameDifficulty d);

	void Init();
	void Update();
	void Draw();
	void DrawSudoku();
};

