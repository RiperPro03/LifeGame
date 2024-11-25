#include "Game.h"

//Public -----------------------------------------

Game::Game(int id, Grid& grid)
    : id(id), grid(grid) {}

void Game::nextGen() {
    Grid& currentGrid = this->grid;

    // Créer une grille temporaire pour stocker les futurs états
    vector<vector<bool>> tempGrid(currentGrid.getWidth(), vector<bool>(currentGrid.getLength(), false));

    // Indicateur pour vérifier si la grille a changé
    bool hasChanged = false;

    // Calculer le prochain état pour chaque cellule dans une grille temporaire
    for (int row = 0; row < currentGrid.getWidth(); ++row) {
        for (int col = 0; col < currentGrid.getLength(); ++col) {
            const int aliveNeighbours = currentGrid.nbNeighbourCellAlive(row, col);
            bool nextState = false;

            if (currentGrid.getCell(row, col).getState()) { // Si cellule vivante
                nextState = (aliveNeighbours == 2 || aliveNeighbours == 3);
            } else { // Si cellule morte
                nextState = (aliveNeighbours == 3);
            }

            // Vérifier si l'état futur est différent de l'état actuel
            if (currentGrid.getCell(row, col).getState() != nextState) {
                hasChanged = true; // Il y a eu un changement dans la grille
            }

            // Stocker l'état futur dans la grille temporaire
            tempGrid[row][col] = nextState;
        }
    }

    // Si aucun changement n'a été détecté, arrêter le jeu
    if (!hasChanged) {
        this->state = false; // Mettre l'état du jeu à "fini"
        cout << "Le jeu s'est stabilise ou toutes les cellules sont mortes a la generation " << this->currentGen << "." << endl;
        return;
    }

    // Appliquer les nouveaux états à la grille actuelle
    for (int row = 0; row < currentGrid.getWidth(); ++row) {
        for (int col = 0; col < currentGrid.getLength(); ++col) {
            currentGrid.getCell(row, col).setState(tempGrid[row][col]);
        }
    }

    // Sauvegarder la génération et incrémenter le compteur de générations
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
    // Nom du dossier où les fichiers seront sauvegardés
    const string folder = "out";

    // Vérifier si le dossier existe, sinon le créer
    if (!filesystem::exists(folder)) {
        filesystem::create_directory(folder);
    }

    // Construire le chemin complet du fichier dans le dossier "out"
    const string filename = folder + "/generation_" + to_string(this->getCurrentGen()) + ".txt";
    ofstream outFile(filename);

    if (!outFile.is_open()) {
        cerr << "Erreur lors de l'ouverture du fichier pour la sauvegarde." << endl;
        return;
    }

    // Écrire la grille dans le fichier
    for (const auto& row : grid) {
        for (bool cellState : row) {
            outFile << (cellState ? '1' : '0');  // Écrire '1' pour vivant, '0' pour mort
        }
        outFile << '\n';
    }

    outFile.close();

    cout << "Grille " << to_string(this->getCurrentGen()) << " sauvegardee avec succes dans " << filename << endl;
}