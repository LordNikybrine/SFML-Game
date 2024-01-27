#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

class Game {
public:
	Game();
	void run();

private:
	void processEvents();
	void check_player_movement();
	void enemys();
	void check_for_hit();
	void updateHitsText();
	void update();
	void render();

private:
	sf::RenderWindow window;
	sf::RectangleShape rectangle;
	sf::CircleShape enemy;
	sf::Sprite rectanngle;
	sf::Vector2f direction = { 0.2f, 0.2f };

	sf::Font font;
	sf::Texture texture;
	sf::Text hitsText;

	bool wasColliding = false;

	int hits = 0;

	float enemySpeed = 0.3;
	float playerSpeed = 0.2;
};

Game::Game() : window(sf::VideoMode(1680 / 2, 1050 / 2), "Spiel", sf::Style::Default, sf::ContextSettings(0, 0, 8)) {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	if (!font.loadFromFile("./assets/Roboto-Regular.ttf")) {
		//! Irgendwie fehler behandeln
	}
	hitsText.setFont(font);
	hitsText.setCharacterSize(24);
	hitsText.setFillColor(sf::Color::White);
	hitsText.setPosition(10, 10);

	if (!texture.loadFromFile("./assets/player.png")) {
		//! Irgendwie fehler behandeln
	}
	rectangle.setPosition(sf::Vector2f(250, 250));
	texture.setSmooth(true);
	rectangle.setTexture(&texture);

	enemy.setRadius(25);
	enemy.setFillColor(sf::Color::Red);
	rectangle.setSize(sf::Vector2f(50, 50));
	rectangle.setPosition(sf::Vector2f(250, 250));

	enemySpeed = window.getSize().x * 0.0004;
	playerSpeed = window.getSize().x * 0.0002;
}

void Game::processEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		if (event.type == sf::Event::Resized) {
			//TODO: proportionen beibehalten
		}
	}
}

void Game::run() {
	while (window.isOpen()) {
		processEvents();
		update();
		render();
	}
}

void Game::check_player_movement() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		rectangle.move(-playerSpeed, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		rectangle.move(playerSpeed, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		rectangle.move(0, -playerSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		rectangle.move(0, playerSpeed);

	if (rectangle.getPosition().x < 0) {
		rectangle.setPosition(0, rectangle.getPosition().y);
	}
	if (rectangle.getPosition().x > window.getSize().x -50) {
		rectangle.setPosition(window.getSize().x -50, rectangle.getPosition().y);
	}

	if (rectangle.getPosition().y < 0) {
		rectangle.setPosition(rectangle.getPosition().x, 0);
	}
	if (rectangle.getPosition().y > window.getSize().y - 50) {
		rectangle.setPosition(rectangle.getPosition().x, window.getSize().y - 50);
	}
}

void Game::enemys() {
	enemy.move(direction.x * enemySpeed, direction.y * enemySpeed);

	if (enemy.getPosition().x < 0 || enemy.getPosition().x > window.getSize().x) {
		direction.x = -direction.x;
	}

	if (enemy.getPosition().y < 0 || enemy.getPosition().y > window.getSize().y) {
		direction.y = -direction.y;
	}
}

void Game::check_for_hit(){
	bool isColliding = enemy.getGlobalBounds().intersects(rectangle.getGlobalBounds());

	if (isColliding && !wasColliding) {
		hits++;
	}

	wasColliding = isColliding;
}

void Game::updateHitsText() {
	hitsText.setString("Hits: " + std::to_string(hits));
}

void Game::update() {
	check_player_movement();
	enemys();
	check_for_hit();
	updateHitsText();
}

void Game::render() {
	window.clear(sf::Color::Black);
	window.draw(enemy);
	window.draw(rectangle);
	window.draw(hitsText);
	window.display();
}

int main() {
	Game game;
	game.run();

	return 0;
}


/*
#include <SFML/Graphics.hpp>

class Game {
public:
	Game();
	void run();

private:
	void processEvents();
	void update();
	void render();

private:
	sf::RenderWindow window;
};

Game::Game() : window(sf::VideoMode(800, 600), "Spiel") {
	// Hier können Sie Initialisierungsfunktionen hinzufügen, falls benötigt
}

void Game::processEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Game::update() {
	// Hier können Sie Update-Logik hinzufügen, falls benötigt
}

void Game::render() {
	window.clear();
	// Hier können Sie Renderelemente hinzufügen, falls benötigt
	window.display();
}

void Game::run() {
	while (window.isOpen()) {
		processEvents();
		update();
		render();
	}
}

int main() {
	Game game;
	game.run();

	return 0;
}
*/

/*
#include <SFML/Graphics.hpp>

class Game {
public:
	Game();
	void run();

private:
	void initialize();
	void processEvents();
	void checkInput();
	void update();
	void updateEnemies();  // Neue Funktion für die Feindbewegung hinzugefügt
	void render();

private:
	sf::RenderWindow window;
	sf::CircleShape circle;
	sf::Texture texture;
	sf::CircleShape enemy;
	sf::RectangleShape boundary;
	float playerSpeed;
	float enemySpeed;
	int collisionCount;
	bool gameOver;
	bool initialized;  // Hinzugefügt, um die Initialisierung einmal durchzuführen
	sf::Vector2f direction;  // Hinzugefügt, um die Bewegungsrichtung des Feindes zu speichern
};

Game::Game() : window(sf::VideoMode(800, 600), "Kreis"), circle(50), enemy(30), boundary(sf::Vector2f(800, 10)), playerSpeed(0.2f), enemySpeed(0.1f), collisionCount(0), gameOver(false), initialized(false), direction(1.0f, 1.0f) {
	enemy.setFillColor(sf::Color::Red);
	boundary.setPosition(0, 0);
	boundary.setFillColor(sf::Color::Blue);
	initialize();
}

void Game::initialize() {
	circle.setPosition(400, 300);
	if (!texture.loadFromFile("./assets/player.png")) {
		// Handle texture loading failure
	}
	circle.setTexture(&texture);
}

void Game::processEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Game::checkInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		circle.move(-playerSpeed, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		circle.move(playerSpeed, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		circle.move(0, -playerSpeed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		circle.move(0, playerSpeed);
}

void Game::update() {
	// Add additional update logic if needed
	sf::Vector2f newPosition = circle.getPosition();

	// Check if the circle would go beyond the window boundaries
	// ... (same as in the original update function)

	circle.setPosition(newPosition);

	updateEnemies();  // Update für Feind hinzugefügt
}

void Game::updateEnemies() {
	if (!initialized) {
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
		initialized = true;
	}

	sf::Vector2f playerPosition = circle.getPosition();
	enemy.move(direction.x * enemySpeed, direction.y * enemySpeed);

	if (enemy.getPosition().x < 0 || enemy.getPosition().x > window.getSize().x) {
		direction.x = -direction.x;
	}

	if (enemy.getPosition().y < 0 || enemy.getPosition().y > window.getSize().y) {
		direction.y = -direction.y;
	}

	if (enemy.getGlobalBounds().intersects(circle.getGlobalBounds())) {
		sf::Vector2f collisionVector = enemy.getPosition() - playerPosition;
		float collisionAngle = atan2(collisionVector.y, collisionVector.x);
		sf::Vector2f normal = sf::Vector2f(cos(collisionAngle), sin(collisionAngle));
		direction = direction - 2.0f * (direction.x * normal.x + direction.y * normal.y) * normal;

		collisionCount++;

		if (collisionCount >= 1) {
			gameOver = true;
		}
	}
}

void Game::render() {
	window.clear();
	window.draw(circle);
	window.draw(enemy);
	window.draw(boundary);

	if (gameOver) {
		sf::Font font;
		if (font.loadFromFile("./assets/Roboto-Regular.ttf")) {
			sf::Text text("GAME OVER", font, 50);
			text.setPosition(250, 250);
			text.setFillColor(sf::Color::Red);
			window.draw(text);
		}
	}

	window.display();
}

void Game::run() {
	while (window.isOpen()) {
		processEvents();
		checkInput();
		update();
		render();
	}
}

int main() {
	Game game;
	game.run();

	return 0;
}

*/
