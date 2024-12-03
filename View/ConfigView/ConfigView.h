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
    int gridSize = 16;   // Default grid size
    int cellSize = 30;   // Default cell size
    const int configWindowWidth = 400;
    const int configWindowHeight = 200;

    string path = "grille.txt"; // Path to the file containing the grid

    // Helper function for drawing sliders and text
    void drawSlider(sf::RenderWindow& window, sf::RectangleShape& slider, sf::CircleShape& handle, sf::Text& label, int value, int min, int max, sf::Font& font, const sf::Vector2f& position);

public:
    ConfigView() = default;
    void configView();
    void drawView();
};

#endif // CONFIGVIEW_H
