#pragma once
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	void Game::render(sf::RenderWindow & window);
	void Game::events(sf::RenderWindow & window);
	void Game::loop();
	void Game::keyboard(sf::RenderWindow & window);
	void Game::formatWalls();
	bool Game::isCollided(float x, float y);
	bool Game::isWall(int row, int col);
	int Game::whichWall(int row, int col);
	void Game::saveLevel(std::string fname);
	void Game::loadLevel(std::string fname);

	sf::Sprite floor;

	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
};

