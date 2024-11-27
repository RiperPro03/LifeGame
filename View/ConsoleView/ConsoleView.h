#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H


#include "../../Model/Game/Game.h"
#include <iostream>

using namespace std;

class ConsoleView {
private:
    Game& jeu;
public:
    ConsoleView(Game& jeu);
    void afficher() const;
};



#endif
