#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>

using namespace std;

struct GameMessage
{
	sf::Font font;
	sf::Text text;
	void GameOverMessage();
	void GameWinningMessage();
	void draw(sf::RenderWindow& window);

};
