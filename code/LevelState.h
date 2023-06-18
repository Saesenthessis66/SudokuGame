#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "GameData.h"
#include "GameState.h"
#include "MainMenuState.h"

class LevelState : public State
{
	GameDataRef _data;

	sf::Sprite _background;

	sf::Sprite _quitbutton;

	sf::Sprite _easyLevel;
	sf::Sprite _mediumLevel;
	sf::Sprite _hardLevel;
	sf::Sprite _randomLevel;

	sf::Sprite _easy;
	sf::Sprite _medium;
	sf::Sprite _hard;
	sf::Sprite _random;

	sf::Vector2f textOrigin;

public:
	LevelState(GameDataRef data);

	void Init();

	void HandleInput();
	void Update(float dt);
	void Draw(float dt);
	void Animate(float dt);
};