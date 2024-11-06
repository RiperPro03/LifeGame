#include <SFML/Graphics.hpp>

int main()
{
    // Création de la fenêtre principale
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML - Point Vert");

    // Création d'un cercle pour représenter le point vert
    sf::CircleShape point(5); // Rayon de 5 pixels
    point.setFillColor(sf::Color::Green);

    // Positionner le point au centre de la fenêtre
    point.setPosition((window.getSize().x - point.getRadius() * 2) / 2, (window.getSize().y - point.getRadius() * 2) / 2);

    // Boucle principale
    while (window.isOpen())
    {
        // Gestion des événements
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Fermer la fenêtre
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Effacer l'écran
        window.clear();

        // Dessiner le point
        window.draw(point);

        // Afficher la fenêtre
        window.display();
    }

    return EXIT_SUCCESS;
}