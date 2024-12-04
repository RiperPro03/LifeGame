#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "../Cell/Cell.h"


/**
 * @class ObstacleCell
 * @brief Classe représentant une cellule de type obstacle
 *
 * La classe ObstacleCell hérite de la classe Cell et représente une cellule de type obstacle
 * qui ne peut pas changer d'état.
 */
class ObstacleCell : public Cell {
public:
    /**
     * Cellule de type obstacle
     *
     * Crée une cellule de type obstacle qui ne peut pas changer d'état
     *
     * @param row ligne dans la grille
     * @param col colonne dans la grille
     * @param state etat de la cellule
     */
    ObstacleCell(const int row, const int col, const bool state);

    /**
     * Setter de l'état de la cellule
     *
     * Ne fait rien car une cellule de type obstacle ne peut pas changer d'état
     *
     * @param state etat de la cellule
     */
    void setState(bool state) override {}

    /**
     * Permet de savoir si la cellule est un obstacle
     *
     * @return true si la cellule est un obstacle, false sinon
     */
    bool isObstacle() const override;



};



#endif //OBSTACLE_H
