#include "MainMenuState.h"
#include "LevelState.h"
#include "Sudoku.h"
#include "HighScoreState.h"

#include <thread>
#include <sstream>
#include <iostream>

#include "Definitions.h"



MainMenuState::MainMenuState(GameDataRef data) :_data(data)
{
}

void MainMenuState::Init()
{
	_data->assets.LoadTexture(MainMenuBackground, MAIN_MENU_BACKGROUND_FILEPATH);
	_data->assets.LoadTexture(GameTitle, GAME_TITLE_FILEPATH);
	_data->assets.LoadTexture(PlayButton, BUTTON_PLAY_FILEPATH);
	_data->assets.LoadTexture(QuitButton, BUTTON_QUIT_FILEPATH);
	_data->assets.LoadTexture(HighscoreButton, HIGHSCORES_FILEPATH);
	_data->assets.LoadTexture(BackButton, BUTTON_BACK_FILEPATH);

	_data->assets.LoadFont(Default, FONT_FILEPATH);

	_data->assets.LoadTexture(SudokuBackground, SUDOKU_BACKGROUND_FILEPATH);

	_highscoreButton.setScale(.7f,.7f);
	_quitButton.setScale(0.8f, 0.8f);

	_background.setTexture(this->_data->assets.GetTexture(MainMenuBackground));
	_title.setTexture(this->_data->assets.GetTexture(GameTitle));
	_playButton.setTexture(this->_data->assets.GetTexture(PlayButton));
	_highscoreButton.setTexture(this->_data->assets.GetTexture(HighscoreButton));
	_quitButton.setTexture(this->_data->assets.GetTexture(QuitButton));

	_title.setPosition((SCREEN_WIDTH / 2) - (_title.getGlobalBounds().width / 2), _title.getGlobalBounds().width / 10);

}

void MainMenuState::HandleInput()
{
	sf::Event event;

	while (_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			_data->window.close();
		}

		if (_data->input.IsSpriteClicked(_playButton, sf::Mouse::Left, _data->window))
		{
			_data->machine.AddState(StateRef(new LevelState(_data)), true);
		}

		if (_data->input.IsSpriteClicked(_highscoreButton, sf::Mouse::Left, _data->window))
		{
			_data->machine.AddState(StateRef(new HighScoreState(_data)), true);
		}
		
		if (_data->input.IsSpriteClicked(_quitButton, sf::Mouse::Left, _data->window))
		{
			_data->window.close();
		}

	}
}

void MainMenuState::Update(float dt)
{
	this->AnimateButtons(dt);
}

void MainMenuState::Draw(float dt)
{
	_data->window.clear();

	_data->window.draw(_background);
	_data->window.draw(_playButton);
	_data->window.draw(_highscoreButton);
	_data->window.draw(_quitButton);
	_data->window.draw(_title);

	_data->window.display();
}

void MainMenuState::AnimateButtons(float dt)
{
	if (_data->input.IsSpriteHovered(_quitButton, _data->window))
	{
		if (_quitButton.getScale().x < .9f)
		{
			_quitButton.setScale(_quitButton.getScale().x + .1f * dt, _quitButton.getScale().y + .1f * dt);
		}
		_quitButton.setPosition(SCREEN_WIDTH / 2 - (_quitButton.getGlobalBounds().width / 2), 90 * SCREEN_HEIGHT / 100 - (_quitButton.getGlobalBounds().height));
	}
	else
	{
		if (_quitButton.getScale().x > .8f)
		{
			_quitButton.setScale(_quitButton.getScale().x - .5f * dt, _quitButton.getScale().y - .5f * dt);
		}
		_quitButton.setPosition(SCREEN_WIDTH / 2 - (_quitButton.getGlobalBounds().width / 2), 90 * SCREEN_HEIGHT / 100 - (_quitButton.getGlobalBounds().height));
	}

	if (_data->input.IsSpriteHovered(_highscoreButton, _data->window))
	{
		if (_highscoreButton.getScale().x < .75f)
		{
			_highscoreButton.setScale(_highscoreButton.getScale().x + .2f * dt, _highscoreButton.getScale().y + .2f * dt);
		}
		_highscoreButton.setPosition((SCREEN_WIDTH / 2) - (_highscoreButton.getGlobalBounds().width / 2), 50 * SCREEN_HEIGHT / 100 + (_highscoreButton.getGlobalBounds().height * .3f));
	}
	else
	{
		if (_highscoreButton.getScale().x > .7f)
		{
			_highscoreButton.setScale(_highscoreButton.getScale().x - .1f * dt, _highscoreButton.getScale().y - .1f * dt);
		}
		_highscoreButton.setPosition((SCREEN_WIDTH / 2) - (_highscoreButton.getGlobalBounds().width / 2), 50 * SCREEN_HEIGHT / 100 + (_highscoreButton.getGlobalBounds().height * .3f));
	}

	if (_data->input.IsSpriteHovered(_playButton, _data->window))
	{
		if (_playButton.getScale().x < 1.2f)
		{
			_playButton.setScale(_playButton.getScale().x + .5f * dt, _playButton.getScale().y + .5f * dt);
		}
		_playButton.setPosition((SCREEN_WIDTH / 2) - (_playButton.getGlobalBounds().width / 2), 50 * SCREEN_HEIGHT / 100 - (_playButton.getGlobalBounds().height / 2));
	}
	else
	{
		if (_playButton.getScale().x > 1.0f)
		{
			_playButton.setScale(_playButton.getScale().x - .1f * dt, _playButton.getScale().y - .1f * dt);
		}
		_playButton.setPosition((SCREEN_WIDTH / 2) - (_playButton.getGlobalBounds().width / 2), 50 * SCREEN_HEIGHT / 100 - (_playButton.getGlobalBounds().height / 2));
	}
}
