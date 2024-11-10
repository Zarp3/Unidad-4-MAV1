#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

int main() {
    
    RenderWindow window(VideoMode(800, 600), "Sprite Movible con Teclado");

    Texture textureSquare, textureCircle;
    if (!textureSquare.loadFromFile("cuad_yellow.png")) {

    }
    if (!textureCircle.loadFromFile("rcircleg.png")) {

    }

    Sprite sprite;
    sprite.setTexture(textureSquare);

    float spriteSize = 100.0f; 
    sprite.setScale(spriteSize / sprite.getTexture()->getSize().x,
        spriteSize / sprite.getTexture()->getSize().y);

    sprite.setPosition(350, 250);

    bool isSquare = true;

    float moveSpeed = 1.0f;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
                if (isSquare) {
                    sprite.setTexture(textureCircle);
                }
                else {
                    sprite.setTexture(textureSquare);
                }
                isSquare = !isSquare;

                sprite.setScale(spriteSize / sprite.getTexture()->getSize().x,
                    spriteSize / sprite.getTexture()->getSize().y);
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            sprite.move(-moveSpeed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            sprite.move(moveSpeed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            sprite.move(0, -moveSpeed);
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            sprite.move(0, moveSpeed);
        }

        FloatRect bounds = sprite.getGlobalBounds();
        if (bounds.left < 0) sprite.setPosition(0, bounds.top);
        if (bounds.top < 0) sprite.setPosition(bounds.left, 0);
        if (bounds.left + bounds.width > 800) sprite.setPosition(800 - bounds.width, bounds.top);
        if (bounds.top + bounds.height > 600) sprite.setPosition(bounds.left, 600 - bounds.height);

        window.clear(Color::White);
        window.draw(sprite);
        window.display();
    }

    return 0;
}