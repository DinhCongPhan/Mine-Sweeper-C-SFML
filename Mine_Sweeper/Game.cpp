#pragma once
#include "Game.h"
#include "GameMessage.h"
#include "Node.h"
#include <iostream>

using namespace std;


const string PathImage = "images/";
const string PathMusic = "sounds/";
sf::Texture FirstNode, Node0, Node1, Node2, Node3, Node4, Node5, Node6, Node7, Node8, simle, Flag, Mine, wrongFlag;
sf::Sprite Simle;
sf::Music music;
sf::Texture background;
sf::Sprite Background;

void Game::drawTable(int size, int mines) {

	srand((int)time(0));
	table.clear();


	for (int i = 0; i < size; i++) {
		table.push_back(vector<Node>());
		for (int j = 0; j < size; j++) {
			Node c;
			c.kind = 0;
			table.back().push_back(c);

		}
	}
	int r, row, col;
	for (int i = 1; i <= mines; i++) {
		r = rand() % ((size - 1 + 1) * (size - 1 + 1));
		row = (r - 1) / (size - 1 + 1); // Sinh số hàng ngẫu nhiên
		col = r - row * (size - 1 + 1) - 1;
		table[row][col].kind = -1;
	}
	for (vector<Node> arrNode : table) {
		for (Node node : arrNode) {
			cout << node.kind << " ";
		}cout << endl;
	}




}

int Game::getNumOfMine(int i, int j) {
	if (table[i][j].kind == -1) {
		return -1;
	}
	int m = table.size(), n = table[0].size();


	int count = 0;
	int di[] = { -1,  0, 1, 0, -1,  1, 1, -1 };
	int dj[] = { 0, -1, 0, 1, -1, -1, 1,  1 };

	for (int k = 0; k < 8; k++)
	{
		int ii = i + di[k], jj = j + dj[k];
		if (ii >= 0 && jj >= 0 && ii < m && jj < n && table[ii][jj].kind == -1)
			count++;
	}
	return count;
}
void Game::spreadIntoArea(sf::RenderWindow& window, int i, int j) {

	table[i][j].kind = getNumOfMine(i, j);
	if (table[i][j].kind != 0 && table[i][j].kind != -1 && table[i][j].flag == false) {
		table[i][j].lat = true;
		window.draw(table[i][j].LastLayer);
	}
	else {
		int m = table.size(), n = table[0].size();
		if (table[i][j].kind == 0 && table[i][j].lat == false && table[i][j].flag == false) {
			table[i][j].lat = true;
			window.draw(table[i][j].LastLayer);
			int di[] = { -1,  0, 1, 0, -1,  1, 1, -1 };
			int dj[] = { 0, -1, 0, 1, -1, -1, 1,  1 };

			for (int k = 0; k < 8; k++)
			{
				int ii = i + di[k], jj = j + dj[k];
				if (ii >= 0 && jj >= 0 && ii < m && jj < n) {
					if (table[ii][jj].lat == false) {
						spreadIntoArea(window, ii, jj);
					}
				}
			}

		}
	}

}

bool Game::checkForWinning(sf::RenderWindow& window, int m, int n) {
	int count = 0;
	for (vector<Node> arrNode : table) {
		for (Node node : arrNode) {
			if (node.kind != -1 && node.lat == true) {
				count++;
			}
		}
	}
	cout << "count :  " << count << endl;
	int num = m * n - 14;
	if (count == num) {
		return true;
	}
	return false;
}
void Game::printTableAfterEnd(sf::RenderWindow& window, int m, int n) {
	GameMessage g;
	g.GameOverMessage();
	wrongFlag.loadFromFile(PathImage + "WrongFlag.png");
	simle.loadFromFile(PathImage + "LoserSmile.png");
	Simle.setTexture(simle);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)window.close();
		}
		window.clear();
		window.draw(Background);
		window.draw(Simle);
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
			{
				if (table[i][j].flag == true && table[i][j].kind != -1 && table[i][j].lat == false) {
					table[i][j].LastLayer.setTexture(wrongFlag);
				}
				window.draw(table[i][j].LastLayer);    //luc thua
			}

		g.draw(window);
		window.display();
		playAgain(window);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) break;
	}
}
void Game::printTableAfterWin(sf::RenderWindow& window, int m, int n) {
	GameMessage g;
	g.GameWinningMessage();
	simle.loadFromFile(PathImage + "WinnerSmile.png");
	Simle.setTexture(simle);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)window.close();
		}
		window.clear();
		window.draw(Background);
		window.draw(Simle);
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
			{
				if (table[i][j].kind != -1 && table[i][j].lat == true) {
					window.draw(table[i][j].LastLayer);
				}
				else {
					window.draw(table[i][j].FirstLayer);
				}
			}

		g.draw(window);
		window.display();
		playAgain(window);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) break;

	}
}

void Game::updateStatus(sf::RenderWindow& window, int m, int n) {


	background.loadFromFile(PathImage + "Background.png");

	Background.setTexture(background);

	Simle.setTexture(simle);
	Simle.setOrigin(16, 16);
	Simle.setPosition(210, 50);

	sf::Music musicDead;
	musicDead.openFromFile(PathMusic + "Boom.wav");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
		}
		window.clear();
		window.draw(Background);
		window.draw(Simle);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//cout << "click";
			int x = int((sf::Mouse::getPosition(window).x - 18) / 32 - 1);
			int y = int((sf::Mouse::getPosition(window).y - 78) / 32 - 1);
			if (x < m && y < n && x >= 0 && y >= 0)
			{
				spreadIntoArea(window, x, y);
				//table[x][y].lat = true;
				//cout << "true";
				if (checkForWinning(window, m, n)) {

					break;
				}
				if (table[x][y].kind == -1) {

					musicDead.play();
					music.stop();
					break;
				}
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			//cout << "click";
			int x = int((sf::Mouse::getPosition(window).x - 18) / 32 - 1);
			int y = int((sf::Mouse::getPosition(window).y - 78) / 32 - 1);
			if (x < m && y < n && x >= 0 && y >= 0)
			{
				if (table[x][y].flag == false)
				{
					table[x][y].FirstLayer.setTexture(Flag);
					table[x][y].flag = true;
					//cout << "Flag";
				}
				else
				{
					table[x][y].FirstLayer.setTexture(FirstNode);
					table[x][y].flag = false;
				}
			}
		}
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
			{
				window.draw(table[i][j].LastLayer);
			}

		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
			{
				if (!table[i][j].lat) {

					window.draw(table[i][j].FirstLayer);
				}
			}
		window.display();
	}
	if (checkForWinning(window, m, n)) {
		printTableAfterWin(window, m, n);
		//	playAgain(window, m, n);
	}
	else {
		printTableAfterEnd(window, m, n);
		//	playAgain(window, m, n);
	}


}

void Game::playAgain(sf::RenderWindow& window) {

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//cout << "click";
		float x = sf::Mouse::getPosition(window).x;
		float y = sf::Mouse::getPosition(window).y;
		if (x >= 210 && x <= 242 && y >= 50 && y <= 82) {
			drawTable(10, 14);
			playGame(window);
		}
	}
}


void Game::playGame(sf::RenderWindow& window) {

	int m = table.size(), n = table[0].size();
	cout << m << " " << n << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			table[i][j].kind = getNumOfMine(i, j);
			cout << table[i][j].kind << " ";
		}cout << endl;
	}


	music.openFromFile(PathMusic + "/Main.wav");
	music.setLoop(true);
	music.play();

	FirstNode.loadFromFile(PathImage + "Node.png");
	Node0.loadFromFile(PathImage + "0.png");
	Node1.loadFromFile(PathImage + "1.png");
	Node2.loadFromFile(PathImage + "2.png");
	Node3.loadFromFile(PathImage + "3.png");
	Node4.loadFromFile(PathImage + "4.png");
	Node5.loadFromFile(PathImage + "5.png");
	Node6.loadFromFile(PathImage + "6.png");
	Node7.loadFromFile(PathImage + "7.png");
	Node8.loadFromFile(PathImage + "8.png");


	simle.loadFromFile(PathImage + "ClickSmile.png");
	Flag.loadFromFile(PathImage + "Flag.png");

	Mine.loadFromFile(PathImage + "Mine.png");






	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
		{
			table[i][j].FirstLayer.setTexture(FirstNode);
			table[i][j].x = (i + 1) * 32 + 18;
			table[i][j].y = (j + 1) * 32 + 78;
			table[i][j].FirstLayer.setPosition(table[i][j].x, table[i][j].y);
			table[i][j].LastLayer.setPosition(table[i][j].x, table[i][j].y);

			table[i][j].kind = getNumOfMine(i, j);
			switch (table[i][j].kind)
			{
			case -1:
				table[i][j].LastLayer.setTexture(Mine);
				break;
			case 0:
				table[i][j].LastLayer.setTexture(Node0);
				break;
			case 1:
				table[i][j].LastLayer.setTexture(Node1);
				break;
			case 2:
				table[i][j].LastLayer.setTexture(Node2);
				break;
			case 3:
				table[i][j].LastLayer.setTexture(Node3);
				break;
			case 4:
				table[i][j].LastLayer.setTexture(Node4);
				break;
			case 5:
				table[i][j].LastLayer.setTexture(Node5);
				break;
			case 6:
				table[i][j].LastLayer.setTexture(Node6);
				break;
			case 7:
				table[i][j].LastLayer.setTexture(Node7);
				break;
			case 8:
				table[i][j].LastLayer.setTexture(Node8);
				break;

			}
		}
	}

	updateStatus(window, m, n);



}