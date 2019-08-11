#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Node.h"
#include "GameMessage.h"

using namespace std;



struct Game {
	int size;
	vector< vector<Node> > table;
	int mines;
	void drawTable(int size, int mines);
	int getNumOfMine(int i, int j);
	void spreadIntoArea(sf::RenderWindow& window, int i, int j);
	bool checkForWinning(sf::RenderWindow& window, int m, int n);
	void printTableAfterEnd(sf::RenderWindow& window, int m, int n);
	void printTableAfterWin(sf::RenderWindow& window, int m, int n);
	void updateStatus(sf::RenderWindow& window, int m, int n);
	void playAgain(sf::RenderWindow& window);
	void playGame(sf::RenderWindow& window);



};
