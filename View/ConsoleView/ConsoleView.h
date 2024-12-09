#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H


#include "../../Model/Game/Game.h"
#include <iostream>

using namespace std;

class ConsoleView {
private:
    Game& jeu;
public:
    /**
     * Constructeur de la classe ConsoleView
     * @param jeu : le jeu de la vie
     */
    ConsoleView(Game& jeu);

    /**
     * Affiche la grille actuelle dans la console
     */
    void afficher() const;
};



#endif
