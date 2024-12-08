#include "Game.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <thread>

//Public -----------------------------------------

Game::Game(Grid& grid, bool isTorique)
    : grid(grid), isTorique(isTorique) {}

void Game::nextGen() {
    if (!this->state) {
        cout << "Le jeu est deja termine." << endl;
        return;
    }
    Grid& currentGrid = this->grid;
    
    // Créer une grille temporaire pour stocker les futurs états
    vector<vector<bool>> tempGrid(currentGrid.getWidth(), vector<bool>(currentGrid.getLength(), false));
    
    // Indicateur pour vérifier si la grille a changé
    bool hasChanged = false;

    // Fonction pour traiter un segment de la grille
    auto processSegment = [&](int startRow, int endRow) {
        for (int row = startRow; row < endRow; ++row) {
            for (int col = 0; col < currentGrid.getLength(); ++col) {
                const int aliveNeighbours = currentGrid.nbNeighbourCellAlive(row, col, this->isTorique);
                bool nextState = false;

                // Si cellule vivante
                if (currentGrid.getCell(row, col).getState()) {
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
    };

    // Déterminer le nombre de threads à utiliser et répartir les lignes de la grille
    const int numThreads = min(static_cast<int>(thread::hardware_concurrency()), currentGrid.getWidth());
    const int totalRows = currentGrid.getWidth();
    const int rowsPerThread = totalRows / numThreads;
    const int remainderRows = totalRows % numThreads;

    vector<thread> threads;

    // Créer les threads pour traiter chaque segment de la grille
    for (int i = 0; i < numThreads; ++i) {
        int startRow = i * rowsPerThread + min(i, remainderRows);
        int endRow = startRow + rowsPerThread + (i < remainderRows ? 1 : 0);

        threads.emplace_back(processSegment, startRow, endRow);
    }

    // Attendre que tous les threads se terminent
    for (auto& t : threads) {
        t.join();
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

    this->currentGen++;
    // Sauvegarder la génération actuelle dans un fichier texte
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

void Game::setState(bool state) {
    this->state = state;
}

//Private -----------------------------------------

void Game::saveGen(vector<vector<bool>>& grid) const {
    // Nom du fichier de sauvegarde
    string inputFileName = this->grid.getName();

    // Extraire le nom de base sans extension
    size_t lastDot = inputFileName.find_last_of('.');
    size_t lastSlash = inputFileName.find_last_of("/\\");
    string baseName = inputFileName.substr(lastSlash + 1, lastDot - lastSlash - 1);

    // Nom du dossier où les fichiers seront sauvegardés
    const string folder = baseName + "_out";

    // Vérifier si le dossier existe, sinon le créer
    if (!filesystem::exists(folder)) {
        filesystem::create_directory(folder);
    }

    // Construire le chemin complet du fichier dans le dossier
    const string filename = folder + "/generation_" + to_string(this->getCurrentGen()) + ".txt";
    ofstream outFile(filename);

    if (!outFile.is_open()) {
        cout << "Erreur lors de l'ouverture du fichier pour la sauvegarde." << endl;
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