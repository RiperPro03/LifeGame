#include <iostream>
#include "Model/Game/Game.h"
#include "View/ConsoleView/ConsoleView.h"
#include "View/GraphicView/GraphicView.h"
#include "Controller/Controller.h"
#include "Model/Grid/Grid.h"

using namespace std;

int main() {

    const int cellSize = 10;

    // Demander à l'utilisateur de saisir le chemin du fichier de grille
    string chemin;
    cout << "Entrez le chemin du fichier de la grille : ";
    getline(cin, chemin);
    cout << chemin << endl;

    Grid grille(chemin);

    if (!grille.isLoaded()) {
        cerr << "Erreur lors du chargement de la grille. Fin du programme." << endl;
        return 1;
    }

    Game jeu(grille);
    ConsoleView consoleView(jeu);
    GraphicView graphicView(jeu, cellSize);
    Controller controller(jeu, consoleView, graphicView);

    // Demander à l'utilisateur de choisir le mode d'affichage
    int choix;
    std::cout << "Choisissez le mode d'affichage : (1) Console, (2) Graphique : ";
    std::cin >> choix;

    if (choix == 1) {
        cout << "Mode console" << endl;
        controller.playConsoleMode();
    } else if (choix == 2) {
        cout << "Mode graphique" << endl;
        controller.playGraphicMode(250);
    } else {
        std::cerr << "Choix invalide." << std::endl;
    }

    return 0;
}