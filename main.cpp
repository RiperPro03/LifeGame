#include <iostream>
#include "Model/Game/Game.h"
#include "View/ConsoleView/ConsoleView.h"
#include "View/GraphicView/GraphicView.h"
#include "Controller/Controller.h"
#include "Model/Grid/Grid.h"

using namespace std;

int main() {
    // initialiser le jeu
    // Game jeu;

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

    cout << "Grille chargee avec succes :\n";
    grille.afficherGrille();

    for (int row = 0; row < grille.getWidth(); ++row) {
        for (int col = 0; col < grille.getLength(); ++col) {
            const int aliveNeighbours = grille.nbNeighbourCellAlive(row, col);
            cout << "Cellule (" << row << ", " << col << ") : " << aliveNeighbours << " voisins vivants" << endl;
            if (grille.getCell(row, col).getState()) { // Si cellule vivante
                if (aliveNeighbours < 2 || aliveNeighbours > 3)
                    cout << "Cellule (" << row << ", " << col << ") meurt" << endl;
            } else { // Si cellule morte
                if (aliveNeighbours == 3)
                    cout << "Cellule (" << row << ", " << col << ") nait" << endl;
            }
        }
    }

    // Créer les vues (console et graphique)
    // ConsoleView consoleView(jeu);
    // GraphicView graphicView(jeu);  // Taille de cellule pour l'affichage graphique

    // Initialiser le contrôleur
    // Controller controller(jeu, consoleView, graphicView);

    // Demander à l'utilisateur de choisir le mode d'affichage
    // int choix;
    // std::cout << "Choisissez le mode d'affichage : (1) Console, (2) Graphique : ";
    // std::cin >> choix;
    //
    // if (choix == 1) {
    //     // controller.lancerModeConsole();
    //     cout << "Mode console" << endl;
    // } else if (choix == 2) {
    //     // controller.lancerModeGraphique();
    //     cout << "Mode graphique" << endl;
    // } else {
    //     std::cerr << "Choix invalide." << std::endl;
    // }

    return 0;
}