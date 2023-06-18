#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "GameData.h"

class MainMenuState :public State
{
	GameDataRef _data;

	sf::Sprite _background;
	sf::Sprite _title;
	sf::Sprite _playButton;
	sf::Sprite _highscoreButton;
	sf::Sprite _quitButton;

public:
	MainMenuState(GameDataRef data);

	void Init();

	void HandleInput();
	void Update(float dt);
	void Draw(float dt);
	void AnimateButtons(float dt);
};


