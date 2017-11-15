#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Player.h"
#include "Wall.h"
#include "Wire.h"

using namespace std;
Player test;
float speed = 3;

Wire w(3, 3);

vector<Wall> walls;
vector<Wire> wires;

sf::Texture tx;
sf::View view;
sf::Vector2f position(0, 0);

bool paused = false;

Game::Game()
{

	tx.loadFromFile("Images/Floor.png");
	tx.setRepeated(true);
	floor.setTexture(tx);
	floor.setTextureRect(sf::IntRect(0, 0, 5000, 5000));

	sf::RenderWindow window(sf::VideoMode(1300, 720), "The Algorithm");
	window.setFramerateLimit(90);

	formatWalls();

	view.reset(sf::FloatRect(0, 0, 1300, 720));
	view.setViewport(sf::FloatRect(0, 0, 1, 1));
	while (window.isOpen())
	{
		if (!paused) {
			keyboard(window);
			loop();
		}
		events(window);
		render(window);
	}
}

void Game::render(sf::RenderWindow & window)
{

	position.x = test.x + 32 - (1300 / 2);
	position.y = test.y + 32 - (720 / 2);

	if (position.x < 0) {
		position.x = 0;
	}
	if (position.y < 0) {
		position.y = 0;
	}

	if (position.x > 5000 - 1301) {
		position.x = 5000 - 1301;
	}
	if (position.y > 5000 - 721) {
		position.y = 5000 - 721;
	}

	view.reset({position.x, position.y, 1300, 720});

	window.setView(view);
	window.clear({0, 163, 116, 255});
	window.draw(floor);
	for (int i = 0; i < walls.size(); i++) {
		walls[i].show(window);
	}
	for (int i = 0; i < wires.size(); i++) {
		wires[i].show(window);
	}
	test.showTo(window);
	window.display();
}

void Game::events(sf::RenderWindow & window) {
	//handle events
	sf::Event event;

	while (window.pollEvent(event))	
	{
		if (event.type == sf::Event::Closed) window.close();

		if (event.type == sf::Event::KeyPressed) {
			if (!paused) {
				if (event.key.code == sf::Keyboard::C) {
					walls.clear();
				}
				if (event.key.code == sf::Keyboard::P) {
					int r = (int)(sf::Mouse::getPosition(window).y + position.y) / 64;
					int c = (int)(sf::Mouse::getPosition(window).x + position.x) / 64;
					if (!isWall(r, c)) {
						walls.push_back(Wall(r, c, true));
						formatWalls();
					}
				}
				if (event.key.code == sf::Keyboard::X) {
					saveLevel();
				}
				if (event.key.code == sf::Keyboard::Z) {
					loadLevel();
				}
			}
			if (event.key.code == sf::Keyboard::Escape) {
				paused = !paused;
			}
		}

	}
}

void Game::loop()
{

	if (right && !isCollided(speed, 0)) {
		test.x += speed;
	}
	if (left && !isCollided(-speed, 0)) {
		test.x -= speed;
	}
	if (up && !isCollided(0, -speed)) {
		test.y -= speed;
	}
	if (down && !isCollided(0, speed)) {
		test.y += speed;
	}

	if (!up && !down) {
		test.velY = 0;
	}
	if (!right && !left) {
		test.velX = 0;
	}
}

void Game::keyboard(sf::RenderWindow & window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		right = true;
	}
	else {
		right = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		left = true;
	}
	else {
		left = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		down = true;
	}
	else {
		down = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		up = true;
	}
	else {
		up = false;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		int r = (int)(sf::Mouse::getPosition(window).y + position.y) / 64;
		int c = (int)(sf::Mouse::getPosition(window).x + position.x) / 64;
		if (!isWall(r, c)) {
			walls.push_back(Wall(r, c));
			formatWalls();
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		int r = (int)(sf::Mouse::getPosition(window).y + position.y) / 64;
		int c = (int)(sf::Mouse::getPosition(window).x + position.x) / 64;
		if (isWall(r, c)) {
			walls.erase(walls.begin() + whichWall(r, c));
			formatWalls();
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
		int r = (int)(sf::Mouse::getPosition(window).y + position.y) / 64;
		int c = (int)(sf::Mouse::getPosition(window).x + position.x) / 64;
		if (isWall(r, c)) {
			wires.push_back(Wire(r, c));
			formatWalls();
		}
	}
}

void Game::formatWalls()
{
	for (int i = 0; i < walls.size(); i++) {
		if (!walls[i].isPit) {

			int r = walls[i].row;
			int c = walls[i].col;

			if (!isWall(r + 1, c) && !isWall(r - 1, c) && !isWall(r, c + 1) && !isWall(r, c - 1)) {
				walls[i].setImage("Images/Blocks/block.png");
			}
			else if (isWall(r + 1, c) && !isWall(r - 1, c) && !isWall(r, c + 1) && isWall(r, c - 1) && isWall(r + 1, c - 1)) {
				walls[i].setImage("Images/Blocks/block19.png");
			}
			else if (isWall(r + 1, c) && !isWall(r - 1, c) && !isWall(r, c - 1) && isWall(r, c + 1) && isWall(r + 1, c + 1)) {
				walls[i].setImage("Images/Blocks/block16.png");
			}
			else if (!isWall(r + 1, c) && isWall(r - 1, c) && isWall(r, c - 1) && !isWall(r, c + 1) && isWall(r - 1, c - 1)) {
				walls[i].setImage("Images/Blocks/block11.png");
			}
			else if (!isWall(r + 1, c) && isWall(r - 1, c) && !isWall(r, c - 1) && isWall(r, c + 1) && isWall(r - 1, c + 1)) {
				walls[i].setImage("Images/Blocks/block12.png");
			}
			else if (!isWall(r + 1, c) && isWall(r - 1, c) && !isWall(r, c + 1) && !isWall(r, c - 1)) {
				walls[i].setImage("Images/Blocks/block13.png");
			}
			else if (isWall(r + 1, c) && isWall(r - 1, c) && !isWall(r, c + 1) && !isWall(r, c - 1)) {
				walls[i].setImage("Images/Blocks/block22.png");
			}
			else if (isWall(r + 1, c) && !isWall(r - 1, c) && !isWall(r, c + 1) && !isWall(r, c - 1)) {
				walls[i].setImage("Images/Blocks/block5.png");
			}
			else if (!isWall(r + 1, c) && !isWall(r - 1, c) && isWall(r, c + 1) && isWall(r, c - 1)) {
				walls[i].setImage("Images/Blocks/block7.png");
			}
			else if (!isWall(r + 1, c) && !isWall(r - 1, c) && isWall(r, c + 1) && !isWall(r, c - 1)) {
				walls[i].setImage("Images/Blocks/block10.png");
			}
			else if (!isWall(r + 1, c) && !isWall(r - 1, c) && !isWall(r, c + 1) && isWall(r, c - 1)) {
				walls[i].setImage("Images/Blocks/block9.png");
			}
			else if (!isWall(r + 1, c) && isWall(r - 1, c) && !isWall(r, c + 1) && isWall(r, c - 1)) {
				walls[i].setImage("Images/Blocks/block17.png");
			}
			else if (!isWall(r + 1, c) && isWall(r - 1, c) && isWall(r, c + 1) && !isWall(r, c - 1)) {
				walls[i].setImage("Images/Blocks/block20.png");
			}
			else if (isWall(r + 1, c) && !isWall(r - 1, c) && isWall(r, c + 1) && !isWall(r, c - 1)) {
				walls[i].setImage("Images/Blocks/block21.png");
			}
			else if (isWall(r + 1, c) && !isWall(r - 1, c) && !isWall(r, c + 1) && isWall(r, c - 1)) {
				walls[i].setImage("Images/Blocks/block18.png");
			}
			else if (!isWall(r + 1, c) && isWall(r - 1, c) && isWall(r, c + 1) && isWall(r, c - 1) && !isWall(r - 1, c + 1) && !isWall(r - 1, c - 1)) {
				walls[i].setImage("Images/Blocks/block27.png");
			}
			else if (!isWall(r + 1, c) && isWall(r - 1, c) && isWall(r, c + 1) && isWall(r, c - 1)) {
				walls[i].setImage("Images/Blocks/block8.png");
			}
			else if (isWall(r + 1, c) && isWall(r - 1, c) && !isWall(r, c + 1) && isWall(r, c - 1) && !isWall(r + 1, c - 1) && !isWall(r - 1, c - 1)) {
				walls[i].setImage("Images/Blocks/block25.png");
			}
			else if (isWall(r + 1, c) && isWall(r - 1, c) && !isWall(r, c + 1) && isWall(r, c - 1)) {
				walls[i].setImage("Images/Blocks/block6.png");
			}
			else if (isWall(r + 1, c) && isWall(r - 1, c) && isWall(r, c + 1) && !isWall(r, c - 1) && !isWall(r - 1, c + 1) && !isWall(r + 1, c + 1)) {
				walls[i].setImage("Images/Blocks/block26.png");
			}
			else if (isWall(r + 1, c) && isWall(r - 1, c) && isWall(r, c + 1) && !isWall(r, c - 1)) {
				walls[i].setImage("Images/Blocks/block14.png");
			}
			else if (isWall(r + 1, c) && !isWall(r - 1, c) && isWall(r, c + 1) && isWall(r, c - 1) && !isWall(r + 1, c + 1) && !isWall(r + 1, c - 1)) {
				walls[i].setImage("Images/Blocks/block24.png");
			}
			else if (isWall(r + 1, c) && !isWall(r - 1, c) && isWall(r, c + 1) && isWall(r, c - 1)) {
				walls[i].setImage("Images/Blocks/block15.png");
			}
			else if (isWall(r + 1, c) && isWall(r - 1, c) && isWall(r, c + 1) && isWall(r, c - 1) && !isWall(r + 1, c + 1) && !isWall(r + 1, c - 1) && !isWall(r - 1, c + 1) && !isWall(r - 1, c - 1)) {
				walls[i].setImage("Images/Blocks/block23.png");
			}
			else {
				walls[i].setImage("Images/Blocks/block4.png");
			}
		}
	}
}

bool Game::isCollided(float x, float y)
{
	for (int i = 0; i < walls.size(); i++) {
		if (sf::FloatRect({ test.x + x + 12, test.y + y + 12}, { 40, 40 }).intersects(walls[i].getBounds())) {
			return true;
		}
	}
	return false;
}

bool Game::isWall(int row, int col)
{
	for (int i = 0; i < walls.size(); i++) {
		if (walls[i].row == row && walls[i].col == col) {
			return true;
		}
	}
	return false;
}

int Game::whichWall(int row, int col)
{
	for (int i = 0; i < walls.size(); i++) {
		if (walls[i].row == row && walls[i].col == col) {
			return i;
		}
	}
	return -1;
}

void Game::saveLevel()
{
	paused = true;
	ofstream f;
	string fname;
	cout << "SAVE LEVEL" << endl;
	cout << "Level Name (or type 'nevermind'):";
	cin >> fname;
	if (fname != "nevermind") {
		f.open("Levels/" + fname + ".txt");
		for (int i = 0; i < walls.size(); i++) {
			f << walls[i].row << " " << walls[i].col << endl;
		}
		f.close();
		cout << "Level Saved." << endl;
	}
	paused = false;
}

void Game::loadLevel() {
	paused = true;
	string fname;
	cout << "LOAD LEVEL" << endl;
	cout << "Level Name (or type 'nevermind'):";
	cin >> fname;

	if (fname != "nevermind") {
		ifstream f("Levels/" + fname + ".txt");

		int r;
		int c;
		walls.clear();
		while (f >> r >> c) {
			cout << "Loading Item (" << r << ", " << c << ")" << endl;
			walls.push_back(Wall(r, c));
			formatWalls();
		}
		f.close();

		cout << "Level Loaded" << endl;
	}
	paused = false;
}

