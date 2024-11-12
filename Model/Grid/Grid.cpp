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
        istringstream streamLigne(ligne);
        vector<Cell> rangee;
        int valeur;
        int col = 0;

        while (streamLigne >> valeur) {
            rangee.push_back(Cell(hauteurTmp, col, valeur == 1));
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
            std::cout << (cell.getState() ? "1 " : "0 ");
        }
        std::cout << "\n";
    }
}

bool Grid::isLoaded() const {
    return this->stateGrid;
}