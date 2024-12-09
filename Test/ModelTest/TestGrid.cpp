#include "../UnitTest.h"
#include "../../Model/Grid/Grid.h"
#include <fstream>

TEST_CASE(TestGridConstructor) {
    string stableGridFile = "stable_grid.txt";
    ofstream outFile;
    outFile << "00000\n"
            << "00110\n"
            << "00110\n"
            << "00000\n"
            << "10000\n";
    outFile.close();
    Grid grid;
    ASSERT_TRUE(grid.loadFromFile(stableGridFile));
}

TEST_CASE(TestGridDimensions) {
    string stableGridFile = "stable_grid.txt";
    ofstream outFile;
    outFile << "00000\n"
            << "00110\n"
            << "00110\n"
            << "00000\n"
            << "10000\n";
    outFile.close();
    Grid grid;
    grid.loadFromFile(stableGridFile);
    ASSERT_EQ(5, grid.getLength());
    ASSERT_EQ(5, grid.getWidth());
}

TEST_CASE(TestGridGetCell) {
    string stableGridFile = "stable_grid.txt";
    ofstream outFile;
    outFile << "00000\n"
            << "00110\n"
            << "00110\n"
            << "00000\n"
            << "10000\n";
    outFile.close();
    Grid grid;
    grid.loadFromFile(stableGridFile);
    Cell& cell = grid.getCell(2, 3);
    ASSERT_EQ(2, cell.getRow());
    ASSERT_EQ(3, cell.getCol());
}

TEST_CASE(TestGridNeighboursAlive) {
    string stableGridFile = "stable_grid.txt";
    ofstream outFile;
    outFile << "00000\n"
            << "00110\n"
            << "00110\n"
            << "00000\n"
            << "10000\n";
    outFile.close();
    Grid grid;
    grid.loadFromFile(stableGridFile);
    int aliveNeighbours = grid.nbNeighbourCellAlive(2, 2, false);
    ASSERT_EQ(3, aliveNeighbours);
}

TEST_CASE(TestGridObstacles) {
    // Création d'un fichier de grille avec des cellules normales et obstacles
    std::string obstacleGridFile = "obstacle_grid.txt";
    std::ofstream outFile(obstacleGridFile);
    outFile << "00000\n"
            << "00230\n"  // 2 = obstacle mort, 3 = obstacle vivant
            << "00320\n"
            << "00001\n"
            << "20002\n";
    outFile.close();

    // Charger la grille depuis le fichier
    Grid grid;
    ASSERT_TRUE(grid.loadFromFile(obstacleGridFile));

    // Vérifie que les cellules obstacles sont correctement identifiées
    Cell& obstacle1 = grid.getCell(1, 2); // Obstacle mort
    ASSERT_TRUE(obstacle1.isObstacle());
    ASSERT_TRUE(!obstacle1.getState()); // Mort

    Cell& obstacle2 = grid.getCell(1, 3); // Obstacle vivant
    ASSERT_TRUE(obstacle2.isObstacle());
    ASSERT_TRUE(obstacle2.getState()); // Vivant

    // Vérifie que l'état des obstacles ne peut pas être modifié
    obstacle1.setState(true);
    ASSERT_TRUE(!obstacle1.getState()); // Doit rester mort

    obstacle2.setState(false);
    ASSERT_TRUE(obstacle2.getState()); // Doit rester vivant
}