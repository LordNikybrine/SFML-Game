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
void render(sf::RenderWindow& window, const sf::CircleShape& circle);

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Kreis");
    sf::CircleShape circle(50);
    sf::Texture texture;

    initialize(window, circle, texture);

    float speed = 0.2f;

    while (window.isOpen()) {
        processEvents(window);
        checkInput(speed, circle);
        update(speed, circle);

        window.clear();
        render(window, circle);
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

void update(float speed, sf::CircleShape& circle) {
    // Hier können weitere Aktualisierungen hinzugefügt werden, wenn nötig
}

void render(sf::RenderWindow& window, const sf::CircleShape& circle) {
    window.draw(circle);
    // Hier können weitere Zeichenanweisungen hinzugefügt werden, wenn nötig
}
