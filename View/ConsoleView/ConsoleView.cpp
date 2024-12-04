#include "ConsoleView.h"

ConsoleView::ConsoleView(Game& jeu) : jeu(jeu) {}

void ConsoleView::afficher() const {
    cout << "Generation " << this->jeu.getCurrentGen() << " : " << endl;
    auto& grid = this->jeu.getGrid();

    for (int row = 0; row < grid.getWidth(); ++row) {
        for (int col = 0; col < grid.getLength(); ++col) {
            const Cell& currentCell = grid.getCell(row, col);

            if (currentCell.isObstacle()) {
                currentCell.getState() ? cout << 'G' : cout << 'R';
            } else {
                currentCell.getState() ? cout << '#' : cout << '.';
            }
        }
        cout << endl;
    }
}