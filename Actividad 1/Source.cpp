#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp> 

int main() {
   
    sf::RenderWindow window(sf::VideoMode(800, 600), "Unidad 4");

    
    sf::Texture MiraTextura;
    if (!MiraTextura.loadFromFile("crosshair.png")) {

    }

    sf::Sprite MiraSprite;
    MiraSprite.setTexture(MiraTextura);

    
    sf::Vector2u textureSize = MiraTextura.getSize();
    MiraSprite.setOrigin(textureSize.x / 2, textureSize.y / 2);

    
    MiraSprite.setPosition(800 / 2, 600 / 2);

    float scaleFactor = 0.2f;
    MiraSprite.setScale(scaleFactor, scaleFactor);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        window.draw(MiraSprite);

        window.display();
    }

    return 0;
}