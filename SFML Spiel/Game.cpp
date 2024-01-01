#include "Game.h"

//Private Functions
void Game::initVars() {
	this->window = nullptr;
}

void Game::initWindow() {
	this->videoMode.height = 768;
	this->videoMode.width = 1024;

	this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);
}

// Constructors // Destrructors
Game::Game() {
	this->initVars();
	this->initWindow();
}

Game::~Game() {
	delete this->window;
}

//functions

const bool Game::running() const {
	return this->window->isOpen();
}

void Game::pollEvents() {
	while (this->window->pollEvent(this->ev)) {

		switch (this->ev.type) {

		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::update(){
	this->pollEvents();
}

//redners game objects
void Game::render() {
	this->window->clear(sf::Color(255, 78, 55, 255));
	//draw game
	this->window->display();
}