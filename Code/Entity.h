#pragma once
class Entity
{
public:
	float x = 0, y = 0, velX = 0, velY = 0, accX = 0, accY = 0, width, height;
	bool isJumping = false, isFlipped = false;
	std::string fname;

	Entity(sf::Vector2f size, sf::Vector2f pos, std::string filename);

	void show(sf::RenderWindow &window);
	sf::Vector2f getPos();
	sf::FloatRect getBounds();

	sf::Texture tx;
	sf::Sprite player;
};
