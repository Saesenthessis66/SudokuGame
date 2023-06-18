#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "GameData.h"
#include "Loader.h"
#include "Definitions.h"
#include "MainMenuState.h"

class HighScoreState : public State
{
	GameDataRef _data;

	sf::Sprite _background;

	sf::Sprite _backButton;

	sf::Text _text;
	sf::Text nums;

	sf::Text _easyScore;
	sf::Text _mediumScore;
	sf::Text _hardScore;
	sf::Text _randomScore;

	sf::Text easyData;
	sf::Text mediumData;
	sf::Text hardData;
	sf::Text randomData;


	Loader* easy;
	Loader* med;
	Loader* hard;
	Loader* rand;

public:
	HighScoreState(GameDataRef data);
	~HighScoreState();

	void Init();

	void HandleInput();
	void Update(float dt);
	void Draw(float dt);
};

