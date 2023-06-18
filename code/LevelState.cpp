#include "LevelState.h"

#include <sstream>
#include <iostream>
#include <thread>

#include "Sudoku.h"
#include "Definitions.h"

LevelState::LevelState(GameDataRef data) :_data(data)
{
	
}

void LevelState::Init()
{
	_data->assets.LoadTexture(LevelSelectBackground, LEVEL_SELECT_BACKGROUND_FILEPATH);

	_data->assets.LoadTexture(EasyLevel, BUTTON_EASY_LEVEL_FILEPATH);
	_data->assets.LoadTexture(MediumLevel, BUTTON_MEDIUM_LEVEL_FILEPATH);
	_data->assets.LoadTexture(HardLevel, BUTTON_HARD_LEVEL_FILEPATH);
	_data->assets.LoadTexture(RandomLevel, BUTTON_RANDOM_LEVEL_FILEPATH);

	_data->assets.LoadTexture(EasyButton, EASY_TEXT_FILEPATH);
	_data->assets.LoadTexture(MediumButton, MEDIUM_TEXT_FILEPATH);
	_data->assets.LoadTexture(HardButton, HARD_TEXT_FILEPATH);
	_data->assets.LoadTexture(RandomButton, RANDOM_TEXT_FILEPATH);
	_data->assets.LoadTexture(NotReadyText, NOT_READY_TEXT_FILEPATH);

	_background.setTexture(this->_data->assets.GetTexture(LevelSelectBackground));
	_quitbutton.setTexture(this->_data->assets.GetTexture(BackButton));

	_easyLevel.setTexture(this->_data->assets.GetTexture(EasyLevel));
	_mediumLevel.setTexture(this->_data->assets.GetTexture(MediumLevel));
	_hardLevel.setTexture(this->_data->assets.GetTexture(HardLevel));
	_randomLevel.setTexture(this->_data->assets.GetTexture(RandomLevel));

	_easy.setTexture(this->_data->assets.GetTexture(EasyButton));
	_medium.setTexture(this->_data->assets.GetTexture(MediumButton));
	_hard.setTexture(this->_data->assets.GetTexture(HardButton));
    _random.setTexture(this->_data->assets.GetTexture(RandomButton));

	_quitbutton.setPosition(SCREEN_WIDTH - (_quitbutton.getGlobalBounds().width ), SCREEN_HEIGHT - (_quitbutton.getGlobalBounds().height));

	_easyLevel.setPosition((_easyLevel.getGlobalBounds().width/5) , 2*SCREEN_HEIGHT/5 - (_easyLevel.getGlobalBounds().height));
	_mediumLevel.setPosition((_easyLevel.getGlobalBounds().width / 5) + 1* SCREEN_WIDTH/3, 2 * SCREEN_HEIGHT / 5 - (_easyLevel.getGlobalBounds().height));
	_hardLevel.setPosition((_easyLevel.getGlobalBounds().width / 5) +2* SCREEN_WIDTH /3, 2 * SCREEN_HEIGHT / 5 - (_easyLevel.getGlobalBounds().height));
	_randomLevel.setPosition((_easyLevel.getGlobalBounds().width / 5) + SCREEN_WIDTH / 12, 9 * SCREEN_HEIGHT / 10 - (_easyLevel.getGlobalBounds().height));

	_easy.setScale(.4f, .4f);
	_medium.setScale(.4f, .4f);
	_hard.setScale(.4f, .4f);
	_random.setScale(.4f, .4f);
	_quitbutton.setScale(.7f,.7f);

	_easy.setPosition(_easyLevel.getPosition().x + 10, _easyLevel.getPosition().y +_easyLevel.getGlobalBounds().height);
	_medium.setPosition(_mediumLevel.getPosition().x -20, _mediumLevel.getPosition().y + _mediumLevel.getGlobalBounds().height);
	_hard.setPosition(_hardLevel.getPosition().x + 10, _hardLevel.getPosition().y + _hardLevel.getGlobalBounds().height);
	_random.setPosition(_randomLevel.getPosition().x -20, _randomLevel.getPosition().y + _randomLevel.getGlobalBounds().height);

	textOrigin = _random.getPosition();
}

void LevelState::HandleInput()
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

void LevelState::Update(float dt)
{
	Animate(dt);

	if (this->_data->assets.activeThread == true)
	{
		_random.setTexture(this->_data->assets.GetTexture(NotReadyText),true);
		_randomLevel.setColor(sf::Color(255, 23, 23,65));
		_random.setPosition(textOrigin.x-35,textOrigin.y);
	}
	else
	{ 
		_random.setTexture(this->_data->assets.GetTexture(RandomButton), true);
		_randomLevel.setColor(sf::Color(255, 255, 255, 255));
		_random.setPosition(textOrigin);
	}



	if (_data->input.IsSpriteClicked(_quitbutton, sf::Mouse::Left, _data->window))
	{
		_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
	}

	if (_data->input.IsSpriteClicked(_easyLevel, sf::Mouse::Left, _data->window))
	{
		_data->machine.AddState(StateRef(new GameState(_data,Easy)), false);
	}

	if (_data->input.IsSpriteClicked(_mediumLevel, sf::Mouse::Left, _data->window))
	{
		_data->machine.AddState(StateRef(new GameState(_data,Medium)), false); 
	}

	if (_data->input.IsSpriteClicked(_hardLevel, sf::Mouse::Left, _data->window))
	{
		_data->machine.AddState(StateRef(new GameState(_data,Hard)), false);
	}

	if (_data->input.IsSpriteClicked(_randomLevel, sf::Mouse::Left, _data->window))
	{
		if (_data->assets.activeThread == false)
		{
			_data->machine.AddState(StateRef(new GameState(_data, Random)), false);
		}
	}
	
}

void LevelState::Draw(float dt)
{
	_data->window.clear();


	_data->window.draw(_background);
	_data->window.draw(_quitbutton);
	_data->window.draw(_easyLevel);
	_data->window.draw(_mediumLevel);
	_data->window.draw(_hardLevel);
	_data->window.draw(_randomLevel);

	_data->window.draw(_easy);
	_data->window.draw(_medium);
	_data->window.draw(_hard);
	_data->window.draw(_random);

	_data->window.display();
}

void LevelState::Animate(float dt)
{
	if (_data->input.IsSpriteHovered(_quitbutton, _data->window))
	{
		if (_quitbutton.getScale().x < 1.1f)
		{
			_quitbutton.setScale(_quitbutton.getScale().x + .1f * dt, _quitbutton.getScale().y + .1f * dt);
		}
		_quitbutton.setPosition(SCREEN_WIDTH - (_quitbutton.getGlobalBounds().width), SCREEN_HEIGHT - (_quitbutton.getGlobalBounds().height));
	}
	else
	{
		if (_quitbutton.getScale().x > 1.f)
		{
			_quitbutton.setScale(_quitbutton.getScale().x - .5f * dt, _quitbutton.getScale().y - .5f * dt);
		}
		_quitbutton.setPosition(SCREEN_WIDTH - (_quitbutton.getGlobalBounds().width), SCREEN_HEIGHT - (_quitbutton.getGlobalBounds().height));
	}
}

