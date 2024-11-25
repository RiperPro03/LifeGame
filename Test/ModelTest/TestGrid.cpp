#include "../UnitTest.h"
#include "../../Model/Grid/Grid.h"

TEST_CASE(TestGridConstructor) {
    Grid grid("../../grille_test.txt");
    ASSERT_TRUE(grid.isLoaded());
}

TEST_CASE(TestGridDimensions) {
    Grid grid("../../grille_test.txt");
    ASSERT_EQ(5, grid.getLength());
    ASSERT_EQ(5, grid.getWidth());
}

TEST_CASE(TestGridGetCell) {
    Grid grid("../../grille_test.txt");
    Cell& cell = grid.getCell(2, 3);
    ASSERT_EQ(2, cell.getRow());
    ASSERT_EQ(3, cell.getCol());
}

TEST_CASE(TestGridNeighboursAlive) {
    Grid grid("../../grille_test.txt");
    int aliveNeighbours = grid.nbNeighbourCellAlive(1, 1);
    ASSERT_EQ(3, aliveNeighbours);
}