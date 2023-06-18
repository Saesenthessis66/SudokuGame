#pragma once

#include<thread>
#include<vector>
#include<SFML/Graphics.hpp>

enum TextureName
{
	SplashBackground, MainMenuBackground, PlayButton, GameTitle, QuitButton, LevelSelectBackground, SudokuBackground, 
	EasyLevel, MediumLevel, HardLevel, RandomLevel, EasyButton, MediumButton, HardButton, RandomButton, Square ,BackButton
	, NotReadyText, HighscoreButton
};
enum FontName
{
	Default
};

class AssetManager
{
		std::map<TextureName, sf::Texture> _textures;
		std::map<FontName, sf::Font> _fonts;

		

	public:
		bool activeThread = false;

		AssetManager() {}
		~AssetManager() {}

		void LoadTexture(TextureName name, std::string fileName);
		sf::Texture& GetTexture(TextureName name);

		void LoadFont(FontName name, std::string fileName);
		sf::Font& GetFont(FontName name);

};




