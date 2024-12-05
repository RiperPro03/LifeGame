#ifndef CONFIGVIEW_H
#define CONFIGVIEW_H
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

/**
 * @class ConfigView
 * @brief Classe permettant la configuration de notre fichier grille.txt (via interface utilisateur)
 */
class ConfigView {
private:
    int minGridSize = 4; // Borne minimale de la taille de la grille
    int maxGridSize = 64; // Borne maximale de la taille de la grille
    int gridSize = (maxGridSize + minGridSize) / 2;   // Taille de la grille par défaut
    
    int minCellSize = 10; // Borne minimale de la taille des cellules
    int maxCellSize = 50; // Borne maximale de la taille des cellules
    int cellSize = (maxCellSize + minCellSize) / 2;   // Taille de la grille par défaut

    int delayGen = 1000; 
    const int configWindowWidth = 400; // Largeur de la fenêtre de config par défaut
    const int configWindowHeight = 250; // Hauteur de la fenêtre de config par défaut



    string path = "grille.txt"; // Chemin du fichier créé

public:
    /**
     * Constructeur par défaut de notre classe
     */
    ConfigView() = default;
    /**
     * Méthode permétant de créer la fenêtre de configuration et de l'afficher
     */
    void configView();
    /**
     *  Méthode permétant de créer la fenêtre de dessin de cellule et de l'afficher
     * Dans cette fenêtre, l'utilisateur pourra dessiner à l'aide de sa souris et de son clavier,
     * des cellules mortes (0) ou vivantes (1).
     */
    void drawView();
    
    // Getters et Setters
    
    /**
     * Obtenir la taille de la grille définis dans configView()
     * @return Taille en nombre de cellule par côté
     */
    int getGridSize();
    /**
     * Obtenir la borne min de la grille définis dans configView()
     * @return Taille en nombre de cellule par côté
     */
    int getMinGridSize();
    /**
     * Obtenir la borne max de la grille définis dans configView()
     * @return Taille en nombre de cellule par côté
     */
    int getMaxGridSize();

    /**
     * Obtenir la taille des cellules définis dans configView()
     * @return Taille en pixel des cellules
     */
    int getCellSize();
    /**
     * Obtenir la borne min des cellules définis dans configView()
     * @return Taille en pixel des cellules
     */
    int getMinCellSize();
    /**
     * Obtenir la borne max des cellules définis dans configView()
     * @return Taille en pixel des cellules
     */
    int getMaxCellSize();

    /**
     * Obtenir le temps entre les génération lors de la simulation définis dans configView()
     * @return Temps en millisecond (1 - 10 000)
     */
    int getDelayGen();

    /**
     * Changer la borne min de la taille de la grille définis dans configView()
     * @param int minGridSize : Borne min de la grille
     */
    void setMinGridSize(int minGridSize);
    /**
     * Changer la borne max de la taille de la grille définis dans configView()
     * @param int maxGridSize : Borne max de la grille
     */
    void setMaxGridSize(int maxGridSize);
    /**
     * Changer la borne min de la taille de la cellule définis dans configView()
     * @param int minCellSize : Borne min de la cellule
     */
    void setMinCellSize(int minCellSize);
    /**
     * Changer la borne max de la taille de la cellule définis dans configView()
     * @param int maxCellSize : Borne max de la cellule
     */
    void setMaxCellSize(int maxCellSize);
};

#endif
