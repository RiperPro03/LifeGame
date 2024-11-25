#ifndef GRID_H
#define GRID_H


#include <vector>
#include <string>
#include "../Cell/Cell.h"
using namespace std;


/**
 * @class Grid
 * @brief Gérer une grille de cellules chargée à partir d'un fichier txt
 *
 * La classe Grid permet de gérer une grille de cellules chargée à partir d'un fichier txt,
 * chaque cellule est accessible par ses coordonnées (x, y).
 */
class Grid {
private:
    int lentgh = 0; // longueur de la grille
    int width = 0; // largeur de la grille
    vector <vector <Cell>> cells; // grille de cellules
    bool stateGrid; // Vrai si la grille est à été créée avec succès

    /**
     * @brief Charge une grille à partir d'un fichier texte.
     *
     * Cette méthode lit un fichier texte dont le chemin est fourni en paramètre,
     * et initialise la grille de cellules en fonction des données du fichier.
     * Le fichier doit contenir uniquement les caractères '1' et '0', représentant respectivement
     * les cellules vivante et morte.
     *
     * @param path Le chemin du fichier texte à charger.
     * @return true si le chargement est réussi, false sinon.
     */
    bool loadFromFile(const string& path);

public:
    /**
     * @brief Constructeur de la classe Grid à partir d'un fichier txt
     *
     * Ce constructeur initialise une instance de la classe Grid
     * en chargeant la grille définie dans le fichier dont le chemin est fourni en paramètre.
     * Il utilise la méthode loadFromFile pour tenter de charger la grille.
     *
     * @param path Le chemin du fichier txt contenant la grille
     */
    Grid(const string& path);

    void afficherGrille() const;

    /**
     * @brief Obtenir une référence à une cellule spécifique de la grille.
     *
     * Cette méthode retourne une référence à la cellule située aux coordonnées
     * spécifiées (row, col) dans la grille.
     *
     * @param row La ligne de la cellule souhaitée (int).
     * @param col La colonne de la cellule souhaitée (int).
     * @return Une référence à l'objet Cell correspondant.
     */
    Cell& getCell(int x, int y);


    /**
     * @brief Retourne la longueur de la grille.
     *
     * Cette méthode retourne la longueur de la grille (nombre de colonnes).
     *
     * @return la longueur de la grille (int).
     */
    int getLength() const;

    /**
     * @brief Retourne la largeur de la grille.
     *
     * Cette méthode retourne la largeur de la grille (nombre de lignes).
     *
     * @return la largeur de la grille (int).
     */
    int getWidth() const;

    /**
     * @brief Vérifie si la grille a été chargée avec succès.
     *
     * @return true si la grille est chargée, false sinon.
     */
    bool isLoaded() const;
};



#endif