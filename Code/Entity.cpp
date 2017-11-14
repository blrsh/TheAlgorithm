#include "SFML/Graphics.hpp"
#include <iostream>
#include "Entity.h"

Entity::Entity(sf::Vector2f size, sf::Vector2f pos, std::string filename) : fname(filename){
	tx.loadFromFile(fname);
	player.setTexture(tx);
	width = 64;
	height = 64;

	x = pos.x;
	y = pos.y;

}

void Entity::show(sf::RenderWindow &window) {
	player.setPosition(x, y);
	x += velX;
	y += velY;
	velX += accX;
	velY += accY;

	window.draw(player);
}

sf::FloatRect Entity::getBounds() { return player.getGlobalBounds(); };

sf::Vector2f Entity::getPos() { return player.getPosition(); }