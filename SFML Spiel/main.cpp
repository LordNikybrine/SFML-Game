#include <SFML/Graphics.hpp>

// Funktionen zur Initialisierung
void initialize(sf::RenderWindow& window, sf::CircleShape& circle, sf::Texture& texture);

// Funktion zur Ereignisverarbeitung
void processEvents(sf::RenderWindow& window);

// Funktion zur Benutzereingabeüberprüfung
void checkInput(float speed, sf::CircleShape& circle);

// Funktion zur Aktualisierung
void update(float speed, sf::CircleShape& circle);

// Funktion zum Zeichnen
void render(sf::RenderWindow& window, const sf::CircleShape& circle, const sf::CircleShape& enemy);

// Funktion für Gegner
void update_enemys(sf::CircleShape& enemy, float speed);

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Kreis");
    sf::CircleShape circle(50);
    sf::Texture texture;

    sf::CircleShape enemy(30);  // Größe des Feinds
    enemy.setFillColor(sf::Color::Red);

    initialize(window, circle, texture);

    float playerSpeed = 0.2f;
    float enemySpeed = 0.1f;

    while (window.isOpen()) {
        processEvents(window);
        checkInput(playerSpeed, circle);
        update(playerSpeed, circle);
        update_enemys(enemy, enemySpeed);

        window.clear();
        render(window, circle, enemy);
        window.display();
    }

    return 0;
}

void initialize(sf::RenderWindow& window, sf::CircleShape& circle, sf::Texture& texture) {
    circle.setPosition(400, 300);

    if (!texture.loadFromFile("./assets/player.png")) {
        return; // Fehlerbehandlung
    }

    circle.setTexture(&texture);
}

void processEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void checkInput(float speed, sf::CircleShape& circle) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        circle.move(-speed, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        circle.move(speed, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        circle.move(0, -speed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        circle.move(0, speed);
}

void update_enemys(sf::CircleShape& enemy, float speed) {
    static bool initialized = false;
    static int direction = 1;
    static float enemySpeed = 0.1f;

    if (!initialized) {
        // Seed für die Zufallsgenerierung initialisieren
        std::srand(std::time(nullptr));
        initialized = true;
    }

    // Aktualisierung der Position des Feinds
    enemy.move(direction * enemySpeed, 0);

    // Wenn der Feind den Rand des Fensters erreicht hat
    if (enemy.getPosition().x < 0 || enemy.getPosition().x > 800) {
        // Zufällige Änderung der Bewegungsrichtung
        direction = (std::rand() % 2 == 0) ? 1 : -1;

        // Setze den Feind auf die gegenüberliegende Seite zurück
        enemy.setPosition((direction == 1) ? 0 : 800, std::rand() % 600);
    }
}


void update(float speed, sf::CircleShape& circle) {
    // Hier können weitere Aktualisierungen hinzugefügt werden, wenn nötig
}

void render(sf::RenderWindow& window, const sf::CircleShape& circle, const sf::CircleShape& enemy) {
    window.draw(circle);
    window.draw(enemy);
    // Hier können weitere Zeichenanweisungen hinzugefügt werden, wenn nötig
}
