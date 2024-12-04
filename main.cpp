#include <iostream>
#include "Model/Game/Game.h"
#include "View/ConsoleView/ConsoleView.h"
#include "View/GraphicView/GraphicView.h"
#include "Controller/Controller.h"
#include "Model/Grid/Grid.h"
#include "View/ConfigView/ConfigView.h"

using namespace std;

int main() {

    
    string chemin;
    Grid grille;

    ConfigView configView;

    configView.configView();
    const int cellSize = configView.getCellSize();


    // Demander à l'utilisateur de saisir le chemin du fichier de grille
    while (true) {
        cout << "Entrez le chemin du fichier de la grille ('exit' pour quitter) : ";
        getline(cin, chemin);

        if (chemin == "exit") {
            cout << "Programme termine" << endl;
            return 0; // Quitter le programme
        }

        grille = Grid(chemin);

        if (grille.isLoaded()) {
            cout << "Grille chargee avec succes :\n";
            break;
        }
    }

    Game jeu(grille);
    ConsoleView consoleView(jeu);
    GraphicView graphicView(jeu, cellSize);
    const Controller controller(jeu, consoleView, graphicView);

    // Demander à l'utilisateur de choisir le mode d'affichage
    int choix;
    while (true) {
        cout << "Choisissez le mode d'affichage : (1) Console, (2) Graphique, (0) Quitter : ";
        cin >> choix;

        switch (choix) {
            case 0:
                cout << "Programme termine" << endl;
                return 0; // Quitter le programme

            case 1:
                cout << "Mode console" << endl;
                controller.playConsoleMode();
                return 0;

            case 2:
                cout << "Mode graphique" << endl;
                controller.playGraphicMode(delayGen);
                return 0;

            default:
                cout << "Choix invalide. Veuillez entrer 1, 2 ou 0 pour quitter." << endl;
                cin.clear(); // Effacer l'état d'erreur
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorer les caractères restants dans le flux
                break;
        }
    }
}