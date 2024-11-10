#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

int main() {
    
    RenderWindow window(VideoMode(800, 600), "Aplicación de Círculos");

    
    vector<CircleShape> circulos;

    
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            
            if (event.type == Event::Closed)
                window.close();

            
            if (event.type == Event::MouseButtonPressed) {
                CircleShape circulo(20); 

                circulo.setPosition(event.mouseButton.x - circulo.getRadius(),
                    event.mouseButton.y - circulo.getRadius());

               
                if (event.mouseButton.button == Mouse::Left) {
                    circulo.setFillColor(Color::Red); 
                }
                else if (event.mouseButton.button == Mouse::Right) {
                    circulo.setFillColor(Color::Blue); 
                }

                circulos.push_back(circulo);
            }
        }
       
        window.clear(Color::White);

        for (const auto& circulo : circulos) {
            window.draw(circulo);
        }
       
        window.display();
    }

    return 0;
}