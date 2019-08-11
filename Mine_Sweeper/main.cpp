#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Game.h"


using namespace std;


int main()
{   
	sf::RenderWindow window(sf::VideoMode(420,500), "Mine Sweeper");
	
	Game g;
	g.drawTable(10,14);
    g.playGame(window);
	

	return 0;
}
