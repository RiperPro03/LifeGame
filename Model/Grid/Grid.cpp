#include "Grid.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>

bool Grid::loadFromFile(const string& chemin) {
    if (chemin.empty()) {
        cout << "Erreur : chemin de fichier vide." << endl;
        return false;
    }

    if (chemin.substr(chemin.find_last_of('.') + 1) != "txt") {
        cout << "Erreur : fichier non valide." << endl;
        return false;
    }

    ifstream fichier(chemin);
    if (!fichier.is_open()) {
        cout << "Erreur : impossible d'ouvrir le fichier " << chemin << endl;
        return false;
    }

    string ligne;
    int hauteurTmp = 0;
    int largeurTmp = 0;

    if (getline(fichier, ligne)) {
        stringstream ss(ligne);
        int firstValue, secondValue;
        ss >> firstValue >> secondValue;

        if (!ss.fail() && ss.eof()) {
            hauteurTmp = firstValue;
            largeurTmp = secondValue;
        } else {
            largeurTmp = static_cast<int>(ligne.size());
            fichier.seekg(0);
        }
    } else {
        cout << "Erreur : fichier vide ou format incorrect." << endl;
        return false;
    }

    vector<vector<unique_ptr<Cell>>> cellulesTmp;

    int currentRow = 0;
    while (getline(fichier, ligne)) {
        // Remove spaces from the line if dimensions were specified
        if (hauteurTmp > 0) {
            erase_if(ligne, ::isspace);
        }

        if (ligne.size() != largeurTmp) {
            cout << "Erreur : lignes de longueurs inegales dans le fichier." << endl;
            return false;
        }

        vector<unique_ptr<Cell>> rangee;
        for (int col = 0; col < largeurTmp; ++col) {
            switch (ligne[col]) {
                case '0':
                    rangee.push_back(make_unique<Cell>(currentRow, col, false));
                    break;
                case '1':
                    rangee.push_back(make_unique<Cell>(currentRow, col, true));
                    break;
                case '2':
                    rangee.push_back(make_unique<ObstacleCell>(currentRow, col, false)); // Obstacle mort
                    break;
                case '3':
                    rangee.push_back(make_unique<ObstacleCell>(currentRow, col, true));  // Obstacle vivant
                    break;
                default:
                    cout << "Erreur : caractere non valide dans le fichier." << endl;
                    return false;
            }
        }

        cellulesTmp.push_back(move(rangee));
        currentRow++;
    }

    if (hauteurTmp > 0 && currentRow != hauteurTmp) {
        cout << "Erreur : nombre de lignes incorrect dans le fichier." << endl;
        return false;
    }

    this->width = currentRow;
    this->lentgh = largeurTmp;
    this->cells = move(cellulesTmp);
    this->name = filesystem::path(chemin).filename().string();

    fichier.close();
    this->state = true;
    return true;
}

Cell& Grid::getCell(const int x, const int y) const {
    // Vérifier que les coordonnées sont valides
    if (x < 0 || x >= this->getWidth() || y < 0 || y >= this->getLength()) {
        throw out_of_range("Coordonnees de cellule invalides.");
    }

    return *(cells[x][y]);
}

int Grid::getLength() const {
    return this->lentgh;
}

int Grid::getWidth() const {
    return this->width;
}
// Grille standard
// int Grid::nbNeighbourCellAlive(const int row, const int col) {
//     int count = 0;
//
//     // Déplacements relatifs pour accéder aux voisins
//     const int offsets[8][2] = {
//         {-1, -1}, {-1, 0}, {-1, 1}, // Voisin du haut
//         { 0, -1},             { 0, 1}, // Voisin de gauche et de droite
//         { 1, -1}, { 1, 0}, { 1, 1} // Voisin du bas
//     };
//
//     // Parcourir tous les déplacements relatifs
//     for (const auto& offset : offsets) {
//         int neighborRow = row + offset[0];
//         int neighborCol = col + offset[1];
//
//         // Vérifier que le voisin est dans les limites de la grille
//         if (neighborRow >= 0 && neighborRow < this->getWidth() &&
//             neighborCol >= 0 && neighborCol < this->getLength()) {
//             count += this->getCell(neighborRow, neighborCol).getState();
//             }
//     }
//
//     return count;
// }

// Grille torique
int Grid::nbNeighbourCellAlive(const int row, const int col, const bool isTorique) const {
    int count = 0;

    // Déplacements relatifs pour accéder aux voisins
    const int offsets[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1}, // Voisins du haut
        { 0, -1},          { 0, 1}, // Voisins à gauche et à droite
        { 1, -1}, { 1, 0}, { 1, 1}  // Voisins du bas
    };

    for (const auto& offset : offsets) {
        int neighborRow = row + offset[0];
        int neighborCol = col + offset[1];

        if (isTorique) {
            // Logique torique : les indices "débordent" et reviennent au début/fin
            neighborRow = (neighborRow + this->getWidth()) % this->getWidth();
            neighborCol = (neighborCol + this->getLength()) % this->getLength();
        } else {
            // Logique standard : ignorer les voisins hors des limites
            if (neighborRow < 0 || neighborRow >= this->getWidth() ||
                neighborCol < 0 || neighborCol >= this->getLength()) {
                continue;
                }
        }

        // Compter l'état vivant du voisin
        count += this->getCell(neighborRow, neighborCol).getState();
    }

    return count;
}

string Grid::getName() const {
    return this->name;
}

bool Grid::isLoaded() const {
    return this->state;
}