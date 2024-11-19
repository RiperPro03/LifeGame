#include "Grid.h"

#include <algorithm>
#include <fstream>
#include <iostream>

//Public -----------------------------------------

Grid::Grid(const string& chemin) {
    this->stateGrid = loadFromFile(chemin);
}

Cell& Grid::getCell(int row, int col) {
    return cells[row][col];
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