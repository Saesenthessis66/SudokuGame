#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "GameData.h"

class SplashState:public State
{
	GameDataRef _data;

	sf::Clock _clock;

	sf::Sprite _background;

public:
	SplashState(GameDataRef data);

	void Init();

	void HandleInput();
	void Update(float dt);
	void Draw(float dt);
};

