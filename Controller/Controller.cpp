#include "Controller.h"

Controller::Controller(Game& jeu, ConsoleView& consoleView, GraphicView& graphicView) : jeu(jeu), consoleView(consoleView), graphicView(graphicView) {}


void Controller::lancerModeConsole() const {
    while (!jeu.isFinished()) {
        consoleView.afficher();
        jeu.nextGen();
    }
}