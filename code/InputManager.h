#pragma once

#include <SFML/Graphics.hpp>

class InputManager
{

public:
	InputManager() {}
	~InputManager() {}

	bool IsSpriteHovered(sf::Sprite object, sf::RenderWindow& window);

	bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window);

	bool IsRectangleClicked(sf::RectangleShape object, sf::Mouse::Button button, sf::RenderWindow& window);

	bool IsRectangleHovered(sf::RectangleShape object, sf::RenderWindow& window);


	sf::Vector2i GetMousePosition(sf::RenderWindow& window);
};;

