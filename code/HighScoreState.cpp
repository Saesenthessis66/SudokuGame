#include "HighScoreState.h"

HighScoreState::HighScoreState(GameDataRef data): _data(data)
{

}

void HighScoreState::Init()
{
	_data->assets.LoadFont(Default, FONT_FILEPATH);

	_data->assets.LoadTexture(SudokuBackground, SUDOKU_BACKGROUND_FILEPATH);

	_background.setTexture(this->_data->assets.GetTexture(SudokuBackground));
	_backButton.setTexture(this->_data->assets.GetTexture(BackButton));

	_backButton.setScale(.7f, .7f);
	_backButton.setPosition(SCREEN_WIDTH - (_backButton.getGlobalBounds().width), SCREEN_HEIGHT - (_backButton.getGlobalBounds().height));

	_text.setFont(_data->assets.GetFont(Default));
	_text.setFillColor(sf::Color::Black);
	_text.setString("highscores");
	_text.setCharacterSize(80);
	_text.setPosition(SCREEN_WIDTH/2-_text.getGlobalBounds().width/2,30 );
	

	_easyScore.setFont(_data->assets.GetFont(Default));
	_easyScore.setFillColor(sf::Color::Black);
	_easyScore.setString("Easy");
	_easyScore.setPosition(_easyScore.getGlobalBounds().width,_text.getGlobalBounds().height + _text.getPosition().y*3);

	_mediumScore.setFont(_data->assets.GetFont(Default));
	_mediumScore.setFillColor(sf::Color::Black);
	_mediumScore.setString("Medium");
	_mediumScore.setPosition(_easyScore.getGlobalBounds().width + SCREEN_WIDTH * .20f, _text.getGlobalBounds().height + _text.getPosition().y * 3);

	_hardScore.setFont(_data->assets.GetFont(Default));
	_hardScore.setFillColor(sf::Color::Black);
	_hardScore.setString("Hard");
	_hardScore.setPosition(_easyScore.getGlobalBounds().width + SCREEN_WIDTH * .50f, _text.getGlobalBounds().height + _text.getPosition().y * 3);

	_randomScore.setFont(_data->assets.GetFont(Default));
	_randomScore.setFillColor(sf::Color::Black);
	_randomScore.setString("Random");
	_randomScore.setPosition(_easyScore.getGlobalBounds().width + SCREEN_WIDTH * .70f, _text.getGlobalBounds().height + _text.getPosition().y * 3);

	nums.setFont(_data->assets.GetFont(Default));
	nums.setFillColor(sf::Color::Black);
	nums.setString("  1.\n 2.\n 3.\n 4.\n 5.\n 6.\n  7.\n 8.\n 9.\n10.");
	nums.setPosition(nums.getGlobalBounds().width*.6f, _text.getGlobalBounds().height*2 + _text.getPosition().y * 3 );

	easy = new Loader(Easy);
	med = new Loader(Medium);
	hard = new Loader(Hard);
	rand = new Loader(Random);

	easyData.setFont(_data->assets.GetFont(Default));
	easyData.setFillColor(sf::Color::Black);
	easyData.setString(easy->getData());

	mediumData.setFont(_data->assets.GetFont(Default));
	mediumData.setFillColor(sf::Color::Black);
	mediumData.setString(med->getData());

	hardData.setFont(_data->assets.GetFont(Default));
	hardData.setFillColor(sf::Color::Black);
	hardData.setString(hard->getData());

	randomData.setFont(_data->assets.GetFont(Default));
	randomData.setFillColor(sf::Color::Black);
	randomData.setString(rand->getData());

	easyData.setPosition(_easyScore.getPosition().x - 5 , _text.getGlobalBounds().height * 2 + _text.getPosition().y * 3);

	mediumData.setPosition(_mediumScore.getPosition().x + mediumData.getGlobalBounds().width/4, _text.getGlobalBounds().height * 2 + _text.getPosition().y * 3);

	hardData.setPosition(_hardScore.getPosition().x, _text.getGlobalBounds().height * 2 + _text.getPosition().y * 3);

	randomData.setPosition(_randomScore.getPosition().x + randomData.getGlobalBounds().width/4, _text.getGlobalBounds().height * 2 + _text.getPosition().y * 3);
}

void HighScoreState::HandleInput()
{
	sf::Event event;

	while (_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			_data->window.close();
		}
	}
}

void HighScoreState::Update(float dt)
{
	if (_data->input.IsSpriteClicked(_backButton, sf::Mouse::Left, _data->window))
	{
		_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
	}
}

void HighScoreState::Draw(float dt)
{
	_data->window.clear();
	
	_data->window.draw(_background);
	_data->window.draw(_backButton);
	_data->window.draw(_text);
	_data->window.draw(nums);

	_data->window.draw(_easyScore);
	_data->window.draw(_mediumScore);
	_data->window.draw(_hardScore);
	_data->window.draw(_randomScore);

	_data->window.draw(easyData);
	_data->window.draw(mediumData);
	_data->window.draw(hardData);
	_data->window.draw(randomData);

	_data->window.display();
}
