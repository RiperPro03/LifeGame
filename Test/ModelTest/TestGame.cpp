#include "../UnitTest.h"
#include "../../Model/Game/Game.h"
#include "../../Model/Grid/Grid.h"
#include <fstream>

// Test pour le constructeur de Game
TEST_CASE(TestGameConstructor) {
    // Exemple de grille stable (bloc 2x2 vivant au centre)
    string stableGridFile = "stable_grid.txt";
    ofstream outFile(stableGridFile);
    outFile << "00000\n"
            << "00110\n"
            << "00110\n"
            << "00000\n"
            << "10000\n";
    outFile.close();
    Grid grid;
    ASSERT_TRUE(grid.loadFromFile(stableGridFile));
    Game game(grid);

    ASSERT_EQ(0, game.getCurrentGen());
}

//Test pour la méthode nextGen
TEST_CASE(TestGameNextGen) {
    string stableGridFile = "stable_grid.txt";
    ofstream outFile(stableGridFile);
    outFile << "00000\n"
            << "00110\n"
            << "00110\n"
            << "00000\n"
            << "10000\n";
    outFile.close();
    Grid grid;
    grid.loadFromFile(stableGridFile);
    Game game(grid);

    int initialGen = game.getCurrentGen();
    game.nextGen();

    ASSERT_EQ(initialGen + 1, game.getCurrentGen());

    // Vérifie l'état des cellules après une génération (dépend des règles du jeu)
    Cell& cell = grid.getCell(2, 3);
    ASSERT_TRUE(cell.getState());

    std::ifstream savedFile("stable_grid_out/generation_1.txt");
    ASSERT_TRUE(savedFile.is_open());

    std::string line;
    while (std::getline(savedFile, line)) {
        ASSERT_TRUE(!line.empty());
    }

    savedFile.close();
}

// Test pour vérifier si le jeu est terminé
TEST_CASE(TestGameIsFinished) {
    string stableGridFile = "stable_grid.txt";
    ofstream outFile(stableGridFile);
    outFile << "00000\n"
            << "00110\n"
            << "00110\n"
            << "00000\n"
            << "10000\n";
    outFile.close();
    Grid grid;
    grid.loadFromFile(stableGridFile);
    Game game(grid);

    ASSERT_TRUE(!game.isFinished());

}

#include "../UnitTest.h" // Inclure la bibliothèque de tests
#include "../../Model/Game/Game.h" // Inclure la classe Game
#include "../../Model/Grid/Grid.h" // Inclure la classe Grid

// Test pour vérifier si le jeu s'arrête lorsque la grille devient stable
TEST_CASE(TestGameStopsWhenStable) {
    // Exemple de grille stable (bloc 2x2 vivant au centre)
    string stableGridFile = "stable_grid.txt";
    ofstream outFile(stableGridFile);
    outFile << "00000\n"
            << "00110\n"
            << "00110\n"
            << "00000\n"
            << "10000\n";
    outFile.close();

    // Charger la grille et initialiser le jeu
    Grid grid;
    grid.loadFromFile(stableGridFile);
    Game game(grid);

    ASSERT_TRUE(!game.isFinished()); // Vérifie que le jeu n'est pas terminé au début

    game.nextGen(); // Passe à la génération suivante
    ASSERT_TRUE(!game.isFinished()); // Le jeu ne doit pas encore être terminé (grille stable mais pas encore détectée)

    game.nextGen(); // Une génération supplémentaire pour détecter la stabilité
    ASSERT_TRUE(game.isFinished()); // Le jeu doit être terminé (grille stable)
}

// Test pour vérifier si le jeu s'arrête lorsque toutes les cellules sont mortes
TEST_CASE(TestGameStopsWhenAllDead) {
    // Exemple de grille où toutes les cellules sont mortes
    string deadGridFile = "dead_grid.txt";
    ofstream outFile(deadGridFile);
    outFile << "00000\n"
            << "00000\n"
            << "00000\n"
            << "00000\n"
            << "00000\n";
    outFile.close();

    // Charger la grille et initialiser le jeu
    Grid grid;
    grid.loadFromFile(deadGridFile);
    Game game(grid);

    ASSERT_TRUE(!game.isFinished()); // Vérifie que le jeu n'est pas terminé au début

    game.nextGen(); // Passe à la génération suivante
    ASSERT_TRUE(game.isFinished()); // Le jeu doit être terminé (toutes les cellules sont mortes)
}