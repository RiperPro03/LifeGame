#include "ConsoleView.h"

ConsoleView::ConsoleView(Game& jeu) : jeu(jeu) {}

void ConsoleView::afficher() const {
    cout << "Generation " << this->jeu.getCurrentGen() << " : " << endl;
    auto& grid = this->jeu.getGrid();
    for (auto row = 0; row < grid.getWidth(); ++row) {
        for (auto col = 0; col < grid.getLength(); ++col) {
            cout << (grid.getCell(row, col).getState() ? '#' : 'O');
        }
        cout << endl;
    }
}