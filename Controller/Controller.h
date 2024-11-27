#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "../Model/Game/Game.h"
#include "../View/ConsoleView/ConsoleView.h"
#include "../View/GraphicView/GraphicView.h"

class Controller {
private:
    Game& jeu;
    ConsoleView& consoleView;
    GraphicView& graphicView;
public:
    Controller(Game& jeu, ConsoleView& consoleView, GraphicView& graphicView);
    void playConsoleMode() const;   // Lance le mode console
    void playGraphicMode() const; // Lance le mode graphique
};



#endif