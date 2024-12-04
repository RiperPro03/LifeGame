#ifndef CELL_H
#define CELL_H

/**
 * @class Cell
 * @brief Classe représentant une cellule dans une grille, avec une position et un état (vivant ou mort)
 */
class Cell {
private:
    int row; // ligne dans la grille
    int col; // colonne dans la grille
    bool state; // état de la cellule

public:

    /**
     * Constructeur de la classe Cell
     * @param row : la ligne de la cellule (int)
     * @param col : la colonne de la cellule (int)
     * @param state : l'état de la cellule (bool)
     */
    Cell(int row, int col, bool state = false);

    // Getters et Setters

    /**
     * Obtenir la ligne de la cellule
     * @return la ligne de la cellule (int)
     */
    int getRow() const;

    /**
     * Obtenir la colonne de la cellule
     * @return la colonne de la cellule (int)
     */
    int getCol() const;

    /**
     * Obtenir l'état de la cellule
     * @return l'état de la cellule (bool)
     */
    bool getState() const;

    /**
     * Modifie l'état de la cellule
     * @param state : le nouvel état de la cellule (bool)
     */
    virtual void setState(bool state);

    virtual bool isObstacle() const;

    virtual ~Cell() = default;

};



#endif
