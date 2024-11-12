#include "Cell.h"

// Constructeur
Cell::Cell(int row, int col, bool state) : row(row), col(col), state(state) {}

// Getters
int Cell::getRow() const {
    return row;
}

int Cell::getCol() const {
    return col;
}

bool Cell::getState() const {
    return state;
}

// Setter pour l'état
void Cell::setState(bool newState) {
    state = newState;
}

// Méthode pour inverser l'état
void Cell::toggleState() {
    state = !state;
}