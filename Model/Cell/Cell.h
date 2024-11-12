#ifndef CELL_H
#define CELL_H

/*
 * Classe Cell
 * Représente une cellule de la grille
 */
class Cell {
private:
    int row; // ligne dans la grille
    int col; // colonne dans la grille
    bool state; // état de la cellule

public:
    // Constructeurs

    /*
     * Constructeur de la classe Cell
     * @param int row : la ligne de la cellule
     * @param int col : la colonne de la cellule
     * @param bool state : l'état de la cellule
     */
    Cell(int row, int col, bool state = false);

    // Getters et Setters

    /*
     * Retourne la ligne de la cellule
     * @return int : la ligne de la cellule
     */
    int getRow() const;

    /*
     * Retourne la colonne de la cellule
     * @return int : la colonne de la cellule
     */
    int getCol() const;

    /*
     * Retourne l'état de la cellule
     * @return bool : l'état de la cellule
     */
    bool getState() const;

    /*
     * Modifie l'état de la cellule
     * @param bool state : le nouvel état de la cellule
     */
    void setState(bool state);

    // Méthodes
    /*
     * Inverse l'état de la cellule
     */
    void toggleState();

};



#endif
