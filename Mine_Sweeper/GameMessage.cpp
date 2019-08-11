#include "GameMessage.h"

#include <iostream>

using namespace std;

void GameMessage::GameOverMessage() {
	if (!font.loadFromFile("fonts/gameOver.ttf"))
	{
		cout << "Error loading gameOver.ttf" << endl;
	}
	text.setFont(font);
	text.setString("Game Over");
	text.setCharacterSize(110); // in pixels, not points!
	// set the color
	text.setFillColor(sf::Color::Red);

	text.setRotation(5);
	// set the text style
	text.setStyle(sf::Text::Bold);
	text.setPosition(sf::Vector2f(110, 155));
}
void GameMessage::GameWinningMessage() {
	if (!font.loadFromFile("fonts/gameOver.ttf"))
	{
		cout << "Error loading gameWinning.ttf" << endl;
	}
	text.setFont(font);
	text.setString("You Win!!!");
	text.setCharacterSize(115); // in pixels, not points!
	// set the color
	text.setFillColor(sf::Color::Red);

	text.setRotation(5);
	// set the text style
	text.setStyle(sf::Text::Bold);
	text.setPosition(sf::Vector2f(110, 155));
}
void  GameMessage::draw(sf::RenderWindow& window) {
	window.draw(text);
}