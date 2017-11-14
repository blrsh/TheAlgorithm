#pragma once
#include <iostream>
#include "Tile.h"
#include "Player.h"
class Wall : public Tile {
public:
	bool isPit = false;
	bool isWire = false;
	Wall(int row, int col, bool pit = false, bool wire = false) : Tile(row, col, "block.png"), isPit(pit) {
		if (isPit) {
			setImage("Images/Blocks/Pit Wall.png");
		}
	}

	void setImage(std::string fname) {
		tx.loadFromFile(fname);
		tile.setTexture(tx);
	}
};