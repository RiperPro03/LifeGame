#include "../UnitTest.h"
#include "../../Model/Grid/Grid.h"
#include <fstream>

TEST_CASE(TestGridConstructor) {
    string stableGridFile = "stable_grid.txt";
    ofstream outFile(stableGridFile);
    outFile << "00000\n"
            << "00110\n"
            << "00110\n"
            << "00000\n"
            << "10000\n";
    outFile.close();
    Grid grid(stableGridFile);
    ASSERT_TRUE(grid.isLoaded());
}

TEST_CASE(TestGridDimensions) {
    string stableGridFile = "stable_grid.txt";
    ofstream outFile(stableGridFile);
    outFile << "00000\n"
            << "00110\n"
            << "00110\n"
            << "00000\n"
            << "10000\n";
    outFile.close();
    Grid grid(stableGridFile);
    ASSERT_EQ(5, grid.getLength());
    ASSERT_EQ(5, grid.getWidth());
}

TEST_CASE(TestGridGetCell) {
    string stableGridFile = "stable_grid.txt";
    ofstream outFile(stableGridFile);
    outFile << "00000\n"
            << "00110\n"
            << "00110\n"
            << "00000\n"
            << "10000\n";
    outFile.close();
    Grid grid(stableGridFile);
    Cell& cell = grid.getCell(2, 3);
    ASSERT_EQ(2, cell.getRow());
    ASSERT_EQ(3, cell.getCol());
}

TEST_CASE(TestGridNeighboursAlive) {
    string stableGridFile = "stable_grid.txt";
    ofstream outFile(stableGridFile);
    outFile << "00000\n"
            << "00110\n"
            << "00110\n"
            << "00000\n"
            << "10000\n";
    outFile.close();
    Grid grid(stableGridFile);
    int aliveNeighbours = grid.nbNeighbourCellAlive(2, 2);
    ASSERT_EQ(3, aliveNeighbours);
}