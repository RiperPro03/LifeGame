#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H


#include "../../Model/Game/Game.h"

class ConsoleView {
private:
    Game& jeu;
public:
    ConsoleView(Game& jeu);
    void afficher();                // Affiche la grille dans la console
};



#endif
