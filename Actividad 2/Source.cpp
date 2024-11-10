#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <vector>

using namespace std;
using namespace sf;

int main() {
    Texture plataforma;
    vector<Sprite> sprites;

    RenderWindow window(VideoMode(800, 600), "Juego de plataformas");

    string imagen = "plataforma.jpg";

    if (!plataforma.loadFromFile(imagen)) {

    }

    float anchoWIDTH = plataforma.getSize().x;
    float alturaHEIGHT = plataforma.getSize().y;

    for (int i = 0; i < 7; i++) {
        Sprite sprite;
        sprite.setTexture(plataforma);
        sprite.setScale(0.15f, 0.2f * (i + 1));
        sprite.setPosition(i * ((anchoWIDTH * 0.15f) + 20), 600 - (i + 1) * anchoWIDTH * 0.15f);
        sprites.push_back(sprite);
    }

    Sprite sprite;
    sprite.setTexture(plataforma);
    sprite.setScale(0.2f * 7, 0.15f);
    sprite.setPosition(7 * ((anchoWIDTH * 0.15f) + 20), alturaHEIGHT * 0.2f * 6.5f);
    sprites.push_back(sprite);

    // Variables para arrastrar
    bool dragging = false;
    Sprite* selectedSprite = nullptr;
    Vector2f offset;

    // Bucle principal de la ventana
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            // Cerrar la ventana si se recibe un evento de cierre
            if (event.type == Event::Closed)
                window.close();

            // Detectar clic del mouse
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                for (auto& sprite : sprites) {
                    if (sprite.getGlobalBounds().contains(mousePos)) {
                        dragging = true;
                        selectedSprite = &sprite;
                        offset = mousePos - sprite.getPosition();
                        break;
                    }
                }
            }

            // Detectar movimiento del mouse
            if (event.type == Event::MouseMoved && dragging && selectedSprite) {
                Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
                selectedSprite->setPosition(mousePos - offset);
            }

            // Detectar cuando se suelta el botón del mouse
            if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                dragging = false;
                selectedSprite = nullptr;
            }
        }

        // Dibujar los sprites en la ventana
        window.clear();
        for (auto& sprite : sprites) {
            window.draw(sprite);
        }
        window.display();
    }

    return 0;
}