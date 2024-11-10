#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

int main() {
    // Crear una ventana inicial de 800x600 píxeles
    RenderWindow window(VideoMode(800, 600), "Ventana Redimensionable");

    // Limites de tamaño
    const unsigned int MIN_WIDTH = 100;
    const unsigned int MIN_HEIGHT = 100;
    const unsigned int MAX_WIDTH = 1000;
    const unsigned int MAX_HEIGHT = 1000;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            // Cerrar la ventana si se recibe un evento de cierre
            if (event.type == Event::Closed)
                window.close();

            // Detectar redimensionamiento de la ventana
            if (event.type == Event::Resized) {
                unsigned int newWidth = event.size.width;
                unsigned int newHeight = event.size.height;

                // Limitar el tamaño de la ventana
                if (newWidth < MIN_WIDTH) newWidth = MIN_WIDTH;
                if (newHeight < MIN_HEIGHT) newHeight = MIN_HEIGHT;
                if (newWidth > MAX_WIDTH) newWidth = MAX_WIDTH;
                if (newHeight > MAX_HEIGHT) newHeight = MAX_HEIGHT;

                // Ajustar el tamaño de la ventana si es necesario
                window.setSize(Vector2u(newWidth, newHeight));
            }
        }

        // Limpiar la ventana con un color de fondo
        window.clear(Color::Black);

        // Dibujar cualquier contenido aquí (si es necesario)

        // Mostrar el contenido en pantalla
        window.display();
    }

    return 0;
}