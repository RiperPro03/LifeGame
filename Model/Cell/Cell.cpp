#include "Cell.h"

// Constructeur
Cell::Cell(int row, int col, bool state) : row(row), col(col), state(state) {}

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