#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(640, 480), "RPG-Game", sf::Style::Titlebar | sf::Style::Close);

	sf::Event ev;

	while (window.isOpen()) {

		//////Event Poll//////
		while (window.pollEvent(ev)){
			switch (ev.type) {

			case sf::Event::Closed: 
				window.close();
				break;

			case sf::Event::KeyPressed: 
				if (ev.key.code == sf::Keyboard::Escape)
					window.close();
					break;
			}
		}

		//////Update//////


		//////Render//////
		window.clear(sf::Color(255, 79, 55, 255)); // Clear old frame
		//draw gmae
		window.display(); //window is done drawing
	}

	return 0;
}