#ifndef GRAPHICVIEW_H
#define GRAPHICVIEW_H


#include <SFML/Graphics.hpp>
#include "../../Model/Game/Game.h"

class GraphicView {
private:
    Game& jeu;                                   // Référence au modèle du jeu de la vie
    int sizeCell;                                // Taille de chaque cellule dans la grille (en pixels)
public:
    GraphicView(Game& jeu, int sizeCell);  // Constructeur avec référence au modèle et taille des cellules

    void afficher(sf::RenderWindow& window);           // Affiche la grille dans une fenêtre SFML
};



#endif
