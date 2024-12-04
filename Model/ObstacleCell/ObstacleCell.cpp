#include "ObstacleCell.h"

ObstacleCell::ObstacleCell(const int row, const int col, const bool state): Cell(row, col, state) {}

bool ObstacleCell::isObstacle() const {
    return true;
}