#include "SplashState.h"
#include "MainMenuState.h"

#include <sstream>
#include <iostream>

#include "Definitions.h"

SplashState::SplashState(GameDataRef data) :_data(data)
{

}

void SplashState::Init()
{
	_data->assets.LoadTexture(SplashBackground, SPLASH_SCENE_BACKGROUND_FILEPATH);

	_background.setTexture(this->_data->assets.GetTexture(SplashBackground));
}

void SplashState::HandleInput()
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

void SplashState::Update(float dt)
{
	if (_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
	{
		_data->machine.AddState(StateRef(new MainMenuState(_data)),true);
	}
}

void SplashState::Draw(float dt)
{
	_data->window.clear();

	_data->window.draw(_background);
	
	_data->window.display();
}
