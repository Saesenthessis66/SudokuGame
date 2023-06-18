#pragma once
#include <SFML/Graphics.hpp>
#include "GameData.h"
#include <vector>
#include "Sudoku.h"
class Tile
{
	sf::RectangleShape shape;
	bool active;
	bool original;

	sf::Text digit;

	sf::Vector2f position;
	sf::Vector2f size;
	std::pair<int,int> id;

public:
	Tile(sf::Vector2f pos, sf::Vector2f size, sf::Font&);

	void Update();

	sf::Text getText();
	sf::RectangleShape getShape();

	void setOriginal(bool y);
	void setDigit(std::string, bool good);
	void setActive(bool);
	void setId(int n, int i);

	void Win();

	std::pair<int,int> getId();
	bool isActive();
	bool isOriginal();
};

