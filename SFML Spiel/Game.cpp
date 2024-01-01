#include "Game.h"

//Private Functions
void Game::initVars(){
	this->window = nullptr;
}

void Game::initWindow(){
	this->videoMode.height = 1024;
	this->videoMode.width = 768;

	this->videoMode.getDesktopMode;
	this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);
}

// Constructors // Destrructors
Game::Game() {

}

Game::~Game() {

}

void Game::update(){

}

void Game::render(){

}



//functions here
