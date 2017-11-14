#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
using namespace std;

class Tile {
public:
	int row = 0, col = 0;
	int width = 64;
	int height = 64;
	string fname;

	sf::Texture tx;
	sf::Sprite tile;

	Tile(int r, int c, string filename) : row(r), col(c), fname(filename){
		tx.loadFromFile(fname);
		tile.setPosition(64 * col, 64 * row);
	}

	void show(sf::RenderWindow &window) {
		tile.setTexture(tx);
		window.draw(tile);
		
	}

	sf::FloatRect getBounds() {
		return tile.getGlobalBounds();
	}
};