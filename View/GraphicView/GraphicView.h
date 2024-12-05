#ifndef GRAPHICVIEW_H
#define GRAPHICVIEW_H


#include <SFML/Graphics.hpp>
#include "../../Model/Game/Game.h"

class GraphicView {
private:
    Game& jeu;
    int cellSize;
public:
    /**
     * Constructeur de la classe GraphicView
     * @param jeu : le jeu de la vie
     * @param cellSize : la taille des cellules
     */
    GraphicView(Game& jeu, int cellSize);  // Constructeur avec référence au modèle et taille des cellules

    /**
     * Affiche la grille dans une fenêtre SFML
     * @param window : la fenêtre SFML
     */
    void display(sf::RenderWindow& window) const;           // Affiche la grille dans une fenêtre SFML

    /**
     * Obtenir la taille des cellules
     * @return la taille des cellules
     */
    int getCellSize() const;  // Obtenir la taille des cellules
};



#endif
