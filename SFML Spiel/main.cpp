#include <SFML/Graphics.hpp>

void initialize(sf::RenderWindow& window, sf::CircleShape& circle, sf::Texture& texture);
void processEvents(sf::RenderWindow& window);
void checkInput(float speed, sf::CircleShape& circle);
void update(float speed, sf::CircleShape& circle);
void render(sf::RenderWindow& window, const sf::CircleShape& circle, const sf::CircleShape& enemy, bool gameOver);
void update_enemys(sf::CircleShape& enemy, float speed, sf::CircleShape& circle, sf::RenderWindow& window, int& collisionCount, bool& gameOver);

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Kreis");
    sf::CircleShape circle(50);
    sf::Texture texture;

    sf::CircleShape enemy(30);
    enemy.setFillColor(sf::Color::Red);

    initialize(window, circle, texture);

    float playerSpeed = 0.2f;
    float enemySpeed = 0.1f;

    int collisionCount = 0;
    bool gameOver = false;

    while (window.isOpen()) {
        processEvents(window);
        checkInput(playerSpeed, circle);
        update(playerSpeed, circle);
        update_enemys(enemy, enemySpeed, circle, window, collisionCount, gameOver);

        window.clear();
        render(window, circle, enemy, gameOver);
        window.display();
    }

    return 0;
}

void initialize(sf::RenderWindow& window, sf::CircleShape& circle, sf::Texture& texture) {
    circle.setPosition(400, 300);

    if (!texture.loadFromFile("./assets/player.png")) {
        return;
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

void update_enemys(sf::CircleShape& enemy, float speed, sf::CircleShape& circle, sf::RenderWindow& window, int& collisionCount, bool& gameOver) {
    static bool initialized = false;
    static float enemySpeed = 0.03f;
    static sf::Vector2f direction = sf::Vector2f(1.0f, 1.0f);

    if (!initialized) {
        std::srand(std::time(nullptr));
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

void update(float speed, sf::CircleShape& circle) {
    // Hier können weitere Aktualisierungen hinzugefügt werden, wenn nötig
}

void render(sf::RenderWindow& window, const sf::CircleShape& circle, const sf::CircleShape& enemy, bool gameOver) {
    window.draw(circle);
    window.draw(enemy);

    if (gameOver) {
        sf::Font font;
        if (font.loadFromFile("./assets/Roboto-Regular.ttf")) {
            sf::Text text("GAME OVER", font, 50);
            text.setPosition(250, 250);
            text.setFillColor(sf::Color::Red);
            window.draw(text);
        }
    }
}
