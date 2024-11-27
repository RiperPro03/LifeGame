#ifndef GAME_H
#define GAME_H


#include "../Grid/Grid.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

class Game {
private:
    Grid& grid;
    bool state = true;
    int currentGen = 0;

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
     * @param grid
     */
    Game(Grid& grid);

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
};



#endif