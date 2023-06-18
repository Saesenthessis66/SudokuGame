#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "GameData.h"
#include "Board.h"

import helper;

class GameState: public State
{
	GameDataRef _data;

	Board* board;

	GameDifficulty _dif;


	sf::Clock _clock;

	sf::Sprite _background;

public:
	GameState(GameDataRef data, GameDifficulty dif);

	void Init();

	void HandleInput();
	void Update(float dt);
	void Draw(float dt);
};

