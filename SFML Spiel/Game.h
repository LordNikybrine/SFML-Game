#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

// Like the game enigne kinda

class Game
{
private:
	//vars
	// window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Private functions
	void initVars();
	void initWindow();

public:
	//Conmstructor & Destructors
	Game();
	virtual ~Game();

	//Func
	void update();
	void render();
};

