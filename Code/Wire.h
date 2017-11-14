#pragma once
#include "Tile.h"

class Wire : public Tile {
public:
	Wire(int row, int col) : Tile(row, col, "Images/Wires/down.png") {
	
	}

	void setImage(std::string fname) {
		tx.loadFromFile(fname);
		tile.setTexture(tx);
	}
};
