#ifndef GRID_H
#define GRID_H


#include <vector>
#include <string>
#include "../Cell/Cell.h"
using namespace std;

/*
 * Classe Grid
 * Représente une grille de cellules
 */
class Grid {
private:
    int lentgh; // longueur de la grille
    int width; // largeur de la grille
    vector <vector <Cell>> cells; // grille de cellules
    bool stateGrid; // Vrai si la grille est à été créée avec succès

    bool loadFromFile(const string& path);

public:
    Grid(const string& path);

    void afficherGrille() const;

    Cell& getCell(int x, int y);
    int getLength() const;
    int getWidth() const;

    bool isLoaded() const;
};



#endif