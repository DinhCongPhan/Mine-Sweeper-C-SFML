#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>

struct Node {
	sf::Sprite FirstLayer;       // firstLayer
	sf::Sprite LastLayer;       // lastLayer
	int kind;                  // isBoom
							  // -1 means boom
	float x;
	float y;
	bool lat;            // true mean is latted
	bool flag;          // true is flaged


	Node() {
		lat = false;
		flag = false;
	}

};