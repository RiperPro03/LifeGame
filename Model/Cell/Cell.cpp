#include "Cell.h"

// Constructeur
Cell::Cell(const int row, const int col, const bool state) : row(row), col(col), state(state) {}

// Getters
int Cell::getRow() const {
    return this->row;
}

int Cell::getCol() const {
    return this->col;
}

bool Cell::getState() const {
    return this->state;
}

// Setter pour l'état
void Cell::setState(bool newState) {
    this->state = newState;
}

// Méthode pour vérifier si la cellule est un obstacle
bool Cell::isObstacle() const {
    return false;
}