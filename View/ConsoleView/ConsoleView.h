#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H


#include "../../Model/Game/Game.h"

class ConsoleView {
private:
    Game& jeu;
public:
    ConsoleView(Game& jeu);
    void afficher() const;
};



#endif
