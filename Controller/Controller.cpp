#include "Controller.h"

Controller::Controller(Game& jeu, ConsoleView& consoleView, GraphicView& graphicView) : jeu(jeu), consoleView(consoleView), graphicView(graphicView) {}


void Controller::playConsoleMode() const {
    while (!jeu.isFinished()) {
        consoleView.afficher();
        jeu.nextGen();
    }
}

void Controller::playGraphicMode(int delay) const {
    sf::RenderWindow window(sf::VideoMode(jeu.getGrid().getLength() * graphicView.getCellSize(), jeu.getGrid().getWidth() * graphicView.getCellSize()), "Game of Life");

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                jeu.setState(false);
                window.close();
            }
        }

        if (!jeu.isFinished()) {
            graphicView.display(window);
            jeu.nextGen();
            sf::sleep(sf::milliseconds(delay));
        }
    }
}
