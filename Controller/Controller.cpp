#include "Controller.h"

Controller::Controller(Game& jeu, ConsoleView& consoleView, GraphicView& graphicView) : jeu(jeu), consoleView(consoleView), graphicView(graphicView) {}


void Controller::playConsoleMode() const {
    while (!jeu.isFinished()) {
        consoleView.afficher();
        jeu.nextGen();
    }
}

void Controller::playGraphicMode() const {
    sf::RenderWindow window(sf::VideoMode(jeu.getGrid().getWidth() * graphicView.getCellSize(), jeu.getGrid().getLength() * graphicView.getCellSize()), "Game of Life");

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        while (!jeu.isFinished()) {
            graphicView.display(window);
            jeu.nextGen();
        }

        sf::sleep(sf::milliseconds(100));
    }
}
