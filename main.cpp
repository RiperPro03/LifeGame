#include <iostream>
#include "Model/Game/Game.h"
#include "View/ConsoleView/ConsoleView.h"
#include "View/GraphicView/GraphicView.h"
#include "Controller/Controller.h"

using namespace std;

int main() {
    // initialiser le jeu
    // Game jeu;

    // Demander à l'utilisateur de saisir le chemin du fichier de grille
    string chemin;
    cout << "Entrez le chemin du fichier de grille : ";
    cin >> chemin;
    cout << chemin << endl;
    // if (!jeu.chargerGrille(chemin)) {
    //     cerr << "Erreur de chargement du fichier." << endl;
    //     return 1;
    // }

    // Créer les vues (console et graphique)
    // ConsoleView consoleView(jeu);
    // GraphicView graphicView(jeu);  // Taille de cellule pour l'affichage graphique

    // Initialiser le contrôleur
    // Controller controller(jeu, consoleView, graphicView);

    // Demander à l'utilisateur de choisir le mode d'affichage
    int choix;
    std::cout << "Choisissez le mode d'affichage : (1) Console, (2) Graphique : ";
    std::cin >> choix;

    if (choix == 1) {
        // controller.lancerModeConsole();
        cout << "Mode console" << endl;
    } else if (choix == 2) {
        // controller.lancerModeGraphique();
        cout << "Mode graphique" << endl;
    } else {
        std::cerr << "Choix invalide." << std::endl;
    }

    return 0;
}