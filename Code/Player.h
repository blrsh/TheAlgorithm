#pragma once
#include "Entity.h"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

class Player : public Entity {
public:
	int frame = 0;
	int counter = 0;
	bool plus = true;
	string names[5] = {"Images/Player/player1.png", "Images/Player/player2.png", "Images/Player/player3.png", "Images/Player/player4.png", "Images/Player/player5.png"};
	float speed = 3;
	Player() : Entity({ 64, 64 }, { 64,  64 }, "Images/Player/player1.png") {}

	void move(float x, float y) {
		velX = x * speed;
		velY = y * speed;
	}

	void showTo(sf::RenderWindow & window) {
		counter++;
		if (counter == 10) {
			counter = 0;
			if (plus) {
				frame++;
			}
			else {
				frame--;
			}
			if (frame == 4 || frame == 0) {
				plus = !plus;
			}
			tx.loadFromFile(names[frame]);
			player.setTexture(tx);
		}
		show(window);

	}
};
