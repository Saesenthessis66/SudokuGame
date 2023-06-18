#include "GameState.h"

#include <sstream>
#include <iostream>


#include "Definitions.h"



GameState::GameState(GameDataRef data, GameDifficulty dif) :_data(data), _dif(dif)
{
	board = new Board(this->_data, dif);
}

void GameState::Init()
{
	_data->assets.LoadTexture(SudokuBackground, SUDOKU_BACKGROUND_FILEPATH);

	_background.setTexture(this->_data->assets.GetTexture(SudokuBackground));
}

void GameState::HandleInput()
{
	sf::Event event;

	while (_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			_data->window.close();
		}
	}
}

void GameState::Update(float dt)
{
	board->Update();
}

void GameState::Draw(float dt)
{
	_data->window.clear();

	_data->window.draw(_background);
	board->Draw();

	_data->window.display();
}

