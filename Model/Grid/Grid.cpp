#include "Grid.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Constructeur
Grid::Grid(const string& chemin) {
    this->stateGrid = loadFromFile(chemin);
}

bool Grid::loadFromFile(const string& chemin) {
    ifstream fichier(chemin);
    if(!fichier.is_open()) {
        cerr << "Erreur : impossible d'ouvrir le fichier " << chemin << endl;
        return false;
    }

    vector<vector<Cell>> cellulesTmp;
    string ligne;
    int hauteurTmp = 0;

    while (getline(fichier, ligne)) {
        vector<Cell> rangee;

        // Parcours chaque caractère de la ligne
        for (int col = 0; col < ligne.size(); ++col) {
            char valeur = ligne[col];
            // Vérifie que la ligne contient uniquement '1' et '0'
            if (valeur == '1' || valeur == '0') {
                // Crée la cellule avec sa position (row, col) et l'état basé sur le caractère
                rangee.emplace_back(hauteurTmp, col, valeur == '1');
            } else {
                cerr << "Erreur : caractere non valide dans le fichier (" << valeur << ")" << endl;
                return false;
            }
        }

        if (hauteurTmp == 0) {
            this->lentgh = rangee.size();  // Définit la largeur au nombre de cellules dans la première ligne
        } else if (rangee.size() != this->lentgh) {
            cerr << "Erreur : ligne de longueur inégale dans le fichier." << endl;
            return false;
        }

        cellulesTmp.push_back(rangee);
        hauteurTmp++;
    }

    this->width = hauteurTmp;
    this->cells = cellulesTmp;

    fichier.close();
    return true;
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