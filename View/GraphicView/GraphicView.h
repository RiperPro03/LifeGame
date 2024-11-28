#ifndef GRAPHICVIEW_H
#define GRAPHICVIEW_H


#include <SFML/Graphics.hpp>
#include "../../Model/Game/Game.h"

class GraphicView {
private:
    Game& jeu;
    int cellSize;
public:
    GraphicView(Game& jeu, int cellSize);  // Constructeur avec référence au modèle et taille des cellules

    void display(sf::RenderWindow& window);           // Affiche la grille dans une fenêtre SFML

    int getCellSize() const;  // Obtenir la taille des cellules

};



#endif
