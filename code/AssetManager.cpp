#include "AssetManager.h"


	void AssetManager::LoadTexture(TextureName name, std::string fileName)
	{
		sf::Texture tex;

		if (tex.loadFromFile(fileName))
		{
			this->_textures[name] = tex;
		}
	}

	sf::Texture& AssetManager::GetTexture(TextureName name)
	{
		return this->_textures.at(name);
	}

	void AssetManager::LoadFont(FontName name, std::string fileName)
	{
		sf::Font font;

		if (font.loadFromFile(fileName))
		{
			this->_fonts[name] = font;
		}
	}

	sf::Font& AssetManager::GetFont(FontName name)
	{
		return this->_fonts.at(name);
	}
