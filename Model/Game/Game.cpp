#include "Game.h"

//Public -----------------------------------------

Game::Game(int id, Grid& grid)
    : id(id), grid(grid) {}

void Game::nextGen() {
    Grid& currentGrid = this->grid;

    vector<vector<bool>> tempGrid(currentGrid.getWidth(), vector<bool>(currentGrid.getLength(), false));

    // Calculer le prochain état pour chaque cellule dans une grille temporaire
    for (int row = 0; row < currentGrid.getWidth(); ++row) {
        for (int col = 0; col < currentGrid.getLength(); ++col) {
            const int aliveNeighbours = currentGrid.nbNeighbourCellAlive(row, col);
            if (currentGrid.getCell(row, col).getState()) { // Si cellule vivante
                tempGrid[row][col] = (aliveNeighbours == 2 || aliveNeighbours == 3);
            } else { // Si cellule morte
                tempGrid[row][col] = (aliveNeighbours == 3);
            }
        }
    }

    // Appliquer les nouveaux états à la grille actuelle
    for (int row = 0; row < currentGrid.getWidth(); ++row) {
        for (int col = 0; col < currentGrid.getLength(); ++col) {
            currentGrid.getCell(row, col).setState(tempGrid[row][col]);
        }
    }

    this->currentGen++;
    this->saveGen(tempGrid);
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

void Game::saveGen(vector<vector<bool>>& grid) const {
    // Ouvrir un fichier pour écrire la grille
    const string filename = "generation_" + to_string(this->getCurrentGen()) + ".txt";
    ofstream outFile(filename);

    if (!outFile.is_open()) {
        cerr << "Erreur lors de l'ouverture du fichier pour la sauvegarde." << endl;
        return;
    }

    for (const auto& row : grid) {
        for (bool cellState : row) {
            outFile << (cellState ? '1' : '0');  // Écrire '1' pour vivant, '0' pour mort
        }
        outFile << '\n';
    }

    outFile.close();

    cout << "Grille" << to_string(this->getCurrentGen()) << "sauvegardee avec succes" << endl;
}