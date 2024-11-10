#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

class Crosshair {
private:
    Sprite sprite;
    Texture texture;

public:
    Crosshair(const string& filename) {
        if (!texture.loadFromFile(filename)) {
            cerr << "Error al cargar crosshair.png" << endl;
        }
        sprite.setTexture(texture);
        sprite.setScale(0.1f, 0.1f); 
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    }

    void update(const RenderWindow& window) {

        sprite.setPosition(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
    }

    void draw(RenderWindow& window) {
        window.draw(sprite);
    }

    FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }
};

class Enemy {
private:
    Sprite sprite;
    Texture texture;

public:
    Enemy(const string& filename) {
        if (!texture.loadFromFile(filename)) {

        }
        sprite.setTexture(texture);
        sprite.setScale(0.2f, 0.2f); 
        sprite.setPosition(rand() % 700 + 50, rand() % 500 + 50); 
    }

    void draw(RenderWindow& window) {
        window.draw(sprite);
    }

    FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }

    bool isClicked(const Vector2i& mousePos) {
        return sprite.getGlobalBounds().contains(static_cast<Vector2f>(mousePos));
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0))); 

    RenderWindow window(VideoMode(800, 600), "Juego de Crosshair", Style::Titlebar | Style::Close);

    Crosshair crosshair("crosshair.png");

    vector<Enemy> enemies;
    int enemiesDefeated = 0;

    enemies.emplace_back("et.png");

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2i mousePos = Mouse::getPosition(window);

                for (auto it = enemies.begin(); it != enemies.end(); ) {
                    if (it->isClicked(mousePos)) {
                        it = enemies.erase(it); 
                        enemiesDefeated++;
                    
                        if (enemiesDefeated < 5) {
                            enemies.emplace_back("et.png");
                        }
                        break;
                    }
                    else {
                        ++it;
                    }
                }
            }
        }

        // Terminar el juego si se derrotaron 5 enemigos
        if (enemiesDefeated >= 5) {
            window.clear(Color::Black);
            sf::sleep(sf::seconds(3));
            break;
        }

        crosshair.update(window);

        window.clear(Color::White);
        for (auto& enemy : enemies) {
            enemy.draw(window);
        }
        crosshair.draw(window);
        window.display();
    }

    return 0;
}
