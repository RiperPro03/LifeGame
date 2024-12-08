#ifndef GAME_H
#define GAME_H


#include "../Grid/Grid.h"
#include <vector>

using namespace std;

/**
 * @class Game
 * @brief Classe représentant le jeu de la vie
 *
 * La classe Game permet de gérer le jeu de la vie, en calculant les générations successives
 * et en sauvegardant les générations dans des fichiers texte.
 */
class Game {
private:
    Grid& grid;
    bool state = true;
    int currentGen = 0;
    bool isTorique = true;

    /**
     * @brief Sauvegarde la génération actuelle dans un fichier texte
     *
     * @param grid La grille booléenne à sauvegarder
     */
    void saveGen(vector<vector<bool>>& grid) const;
public:
    /**
     * @brief Constructeur de la classe Game
     *
     * @param grid la grille du jeu
     * @param isTorique choix de la grille torique ou non (par défaut True)
     */
    Game(Grid& grid, bool isTorique = true);

    /**
     * @brief Permet de passer à la génération suivante
     *
     * Cette méthode calcule la génération suivante en fonction des règles du jeu de la vie,
     * sauvegarde la génération actuelle dans un fichier texte et incrémente le compteur de générations.
     */
    void nextGen();

    /**
     * @brief Obtenir la génération actuelle
     *
     * @return int la génération actuelle
     */
    int getCurrentGen() const;

    /**
     * @brief Permet de savoir si le jeu est terminé
     *
     * @return true si le jeu est terminé, false sinon
     */
    bool isFinished() const;

    /**
     * @brief Obtenir la grille actuelle du jeu
     *
     * @return const Grid& la grille du jeu
     */
     Grid& getGrid() const;

    /**
     * @brief Permet de changer l'état du jeu
     *
     * Permet de mettre fin au jeu si state est false
     *
     * @param state le nouvel état du jeu
     */
    void setState(bool state);
};



#endif