#include "Grid.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

//Public -----------------------------------------

Grid::Grid(const string& chemin) {

    if (chemin.empty()) {
        cout << "Erreur : chemin de fichier vide." << endl;
        this->stateGrid = false;
        return;
    }

    if (chemin.substr(chemin.find_last_of('.') + 1) != "txt") {
        cout << "Erreur : fichier non valide." << endl;
        this->stateGrid = false;
        return;
    }

    this->stateGrid = loadFromFile(chemin);
}

Cell& Grid::getCell(const int x, const int y) {
    return cells[x][y];
}

bool Grid::isLoaded() const {
    return this->stateGrid;
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
int Grid::nbNeighbourCellAlive(const int row, const int col) {
    int count = 0;

    // Déplacements relatifs pour accéder aux voisins
    const int offsets[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1}, // Voisin du haut
        { 0, -1},             { 0, 1}, // Voisin de gauche et de droite
        { 1, -1}, { 1, 0}, { 1, 1} // Voisin du bas
    };

    for (const auto& offset : offsets) {
        // Calculer la position du voisin avec la logique torique
        int neighborRow = (row + offset[0] + this->width) % this->width;
        int neighborCol = (col + offset[1] + this->lentgh) % this->lentgh;

        // Compter l'état vivant du voisin
        count += this->getCell(neighborRow, neighborCol).getState();
    }

    return count;
}

//Private -----------------------------------------

bool Grid::loadFromFile(const string& chemin) {
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

    vector<vector<Cell>> cellulesTmp;

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

        vector<Cell> rangee;
        for (int col = 0; col < largeurTmp; ++col) {
            char valeur = ligne[col];
            if (valeur != '1' && valeur != '0') {
                cout << "Erreur : caractere non valide dans le fichier." << endl;
                return false;
            }
            rangee.emplace_back(currentRow, col, valeur == '1');
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

    fichier.close();
    return true;
}