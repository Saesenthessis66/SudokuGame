#include "Tile.h"

Tile::Tile(sf::Vector2f pos, sf::Vector2f s, sf::Font& f)
{
	active = false;
	original = false;
	shape.setSize(s);
	shape.setPosition(pos);

	position = pos;
	size = s;

	digit.setFont(f);
	digit.setFillColor(sf::Color::Black);
	digit.setCharacterSize(50);
}

void Tile::Update()
{
	if (active == true)
	{
		shape.setFillColor(sf::Color(140, 207, 85, 100));

	}
	else shape.setFillColor(sf::Color(140, 207, 85, 0));

	if (original)
	{
		digit.setFillColor(sf::Color::Black);
	}
	
}

sf::Text Tile::getText()
{
	return digit;
}

sf::RectangleShape Tile::getShape()
{
	return shape;
}

void Tile::setOriginal(bool y)
{
	original = y;
}

void Tile::setDigit(std::string number, bool good)
{
	if (good) { digit.setFillColor(sf::Color::Blue); }
	else { digit.setFillColor(sf::Color::Red); }

	digit.setString(number);
	digit.setPosition(position.x + (size.x / 2) - digit.getGlobalBounds().width / 2, position.y + (size.y / 2) - digit.getGlobalBounds().height + 5);
}

void Tile::setActive(bool a)
{
	active = a;
}

void Tile::setId(int n, int i)
{
	id = std::pair(n, i);
}

void Tile::Win()
{
	original = true;
	digit.setFillColor(sf::Color::Cyan);
}



std::pair<int, int> Tile::getId()
{
	return id;
}

bool Tile::isActive()
{
	return active;
}

bool Tile::isOriginal()
{
	return original;
}
