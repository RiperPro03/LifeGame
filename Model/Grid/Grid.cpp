#include "Grid.h"

#include <algorithm>
#include <fstream>
#include <iostream>

//Public -----------------------------------------

Grid::Grid(const string& chemin) {

    if (chemin.empty()) {
        cerr << "Erreur : chemin de fichier vide." << endl;
        this->stateGrid = false;
        return;
    }

    if (chemin.substr(chemin.find_last_of('.') + 1) != "txt") {
        cerr << "Erreur : fichier non valide." << endl;
        this->stateGrid = false;
        return;
    }

    this->stateGrid = loadFromFile(chemin);
}

Cell& Grid::getCell(const int x, const int y) {
    return cells[x][y];
}

void Grid::afficherGrille() const {
    for (const auto& ligne : this->cells) {
        for (const auto& cell : ligne) {
            cout << (cell.getState() ? "1 " : "0 ");
        }
        cout << "\n";
    }
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

int Grid::nbNeighbourCellAlive(const int row, const int col) {
    int count = 0;

    // Déplacements relatifs pour accéder aux voisins
    const int offsets[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1}, // Voisin du haut
        { 0, -1},             { 0, 1}, // Voisin de gauche et de droite
        { 1, -1}, { 1, 0}, { 1, 1} // Voisin du bas
    };

    // Parcourir tous les déplacements relatifs
    for (const auto& offset : offsets) {
        int neighborRow = row + offset[0];
        int neighborCol = col + offset[1];

        // Vérifier que le voisin est dans les limites de la grille
        if (neighborRow >= 0 && neighborRow < this->getWidth() &&
            neighborCol >= 0 && neighborCol < this->getLength()) {
            count += this->getCell(neighborRow, neighborCol).getState();
            }
    }

    return count;
}

//Private -----------------------------------------

bool Grid::loadFromFile(const string& chemin) {
    ifstream fichier(chemin);
    if (!fichier.is_open()) {
        cerr << "Erreur : impossible d'ouvrir le fichier " << chemin << endl;
        return false;
    }

    vector<vector<Cell>> cellulesTmp;
    string ligne;
    int hauteurTmp = 0;

    while (getline(fichier, ligne)) {
        // Valider toute la ligne avant traitement
        if (!ranges::all_of(ligne, [](char c) { return c == '1' || c == '0'; })) {
            cerr << "Erreur : caractere non valide dans le fichier." << endl;
            return false;
        }

        vector<Cell> rangee;
        rangee.reserve(ligne.size());  // Réserver l'espace nécessaire

        for (int col = 0; col < static_cast<int>(ligne.size()); ++col) {
            char valeur = ligne[col];
            rangee.emplace_back(hauteurTmp, col, valeur == '1');
        }

        if (hauteurTmp == 0) {
            this->lentgh = rangee.size();  // Définit la largeur au nombre de cellules dans la première ligne
        }

        cellulesTmp.push_back(move(rangee));
        hauteurTmp++;
    }

    // Vérifier que toutes les lignes ont la même taille
    if (!ranges::all_of(cellulesTmp,
                        [this](const vector<Cell>& row) { return row.size() == this->getLength(); })) {
        cerr << "Erreur : lignes de longueurs inégales dans le fichier." << endl;
        return false;
                     }

    this->width = hauteurTmp;
    this->cells = move(cellulesTmp);  // Transférer les données finales

    fichier.close();
    return true;
}