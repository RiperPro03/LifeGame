#include "GraphicView.h"

GraphicView::GraphicView(Game& jeu, int cellSize) : jeu(jeu), cellSize(cellSize) {}

void GraphicView::display(sf::RenderWindow &window) {
    // Récupérer la grille depuis l'objet Game
    auto& grid = this->jeu.getGrid();

    // Effacer la fenêtre avant de dessiner
    window.clear();

    // Créer une cellule graphique (rectangle) avec une taille ajustée
    sf::RectangleShape cell(sf::Vector2f(static_cast<float>(this->cellSize) - 1.0f, static_cast<float>(this->cellSize) - 1.0f));

    // Parcourir chaque cellule de la grille
    for (int row = 0; row < grid.getWidth(); ++row) {
        for (int col = 0; col < grid.getLength(); ++col) {
            // Vérifier si la cellule est vivante
            if (grid.getCell(row, col).getState()) {
                // Positionner le rectangle à l'emplacement de la cellule dans la fenêtre
                cell.setPosition(static_cast<float>(col) * static_cast<float>(this->cellSize), static_cast<float>(row) * static_cast<float>(this->cellSize));


                // Dessiner la cellule sur la fenêtre
                window.draw(cell);
            }
        }
    }

    // Afficher les modifications dans la fenêtre
    window.display();
}

int GraphicView::getCellSize() const {
    return this->cellSize;
}
