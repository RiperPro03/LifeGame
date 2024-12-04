#ifndef CONFIGVIEW_H
#define CONFIGVIEW_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class ConfigView {
private:
    int gridSize = 16;   // Taille de la grille par défaut
    int cellSize = 30;   // Taille de la grille par défaut
    const int configWindowWidth = 400;
    const int configWindowHeight = 200;

    string path = "grille.txt"; // Chemin du fichier créé

    // Fonction permettant la création des sliders
    void drawSlider(sf::RenderWindow& window, sf::RectangleShape& slider, sf::CircleShape& handle, sf::Text& label, int value, int min, int max, sf::Font& font, const sf::Vector2f& position);

public:
    ConfigView() = default;
    void configView();
    void drawView();
    int getCellSize();
    int getGridSize();
};

#endif
