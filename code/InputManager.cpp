#include "InputManager.h"

bool InputManager::IsSpriteHovered(sf::Sprite object, sf::RenderWindow& window)
{
	sf::IntRect tempRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

	if (tempRect.contains(sf::Mouse::getPosition(window)))
	{
		return true;
	}
	return false;
}

bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(button))
	{
		sf::IntRect tempRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width,object.getGlobalBounds().height);

		if (tempRect.contains(sf::Mouse::getPosition(window)))
		{
			return true;
		}
	}
	return false;
}

bool InputManager::IsRectangleClicked(sf::RectangleShape object, sf::Mouse::Button button, sf::RenderWindow& window)
{

	if (sf::Mouse::isButtonPressed(button))
	{
		sf::IntRect tempRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

		if (tempRect.contains(sf::Mouse::getPosition(window)))
		{
			return true;
		}
	}
	return false;
}

bool InputManager::IsRectangleHovered(sf::RectangleShape object, sf::RenderWindow& window)
{
	sf::IntRect tempRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

	if (tempRect.contains(sf::Mouse::getPosition(window)))
	{
		return true;
	}
	return false;
}

sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& window)
{
	return sf::Mouse::getPosition(window);
}
