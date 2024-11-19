#include "Game.h"

//Public -----------------------------------------

Game::Game(int id, Grid &grid)
    : id(id), grid(grid) {}

void Game::nextGen() {
    Grid& currentGrid = this->grid;
    Grid tempGrid = currentGrid; // Créer une copie temporaire pour stocker les nouveaux états

    for (int row = 0; row < currentGrid.getWidth(); ++row) {
        for (int col = 0; col < currentGrid.getLength(); ++col) {
            const int aliveNeighbours = currentGrid.nbNeighbourCellAlive(row, col);

            if (currentGrid.getCell(row, col).getState()) { // Si cellule vivante
                if (aliveNeighbours < 2 || aliveNeighbours > 3)
                    tempGrid.getCell(row, col).setState(false);
            } else { // Si cellule morte
                if (aliveNeighbours == 3)
                    tempGrid.getCell(row, col).setState(true);
            }
        }
    }

    grid = move(tempGrid); // Remplacer l'ancienne grille par la nouvelle
    this->saveGen();
    this->currentGen++;
}

int Game::getCurrentGen() const {
    return currentGen;
}

bool Game::isFinished() const {
    return !state;
}

Grid& Game::getGrid() const {
    return grid;
}

//Private -----------------------------------------

void Game::saveGen() {
    // TODO : sauvegarder la grille dans un fichier
    // ...
    // this->state = false;

}

