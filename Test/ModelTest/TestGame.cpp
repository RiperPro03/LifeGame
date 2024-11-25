#include "../UnitTest.h" // Inclure la bibliothèque de test
#include "../../Model/Game/Game.h" // Inclure la classe Game
#include "../../Model/Grid/Grid.h" // Inclure la classe Grid
#include <fstream>

// Test pour le constructeur de Game
TEST_CASE(TestGameConstructor) {
    Grid grid("../../grille_test.txt"); // Charger une grille depuis un fichier valide
    Game game(1, grid);

    ASSERT_EQ(0, game.getCurrentGen()); // Vérifie que la génération actuelle est initialisée à 1
    ASSERT_TRUE(game.getGrid().isLoaded()); // Vérifie que la grille est bien chargée
}

// Test pour la méthode nextGen
TEST_CASE(TestGameNextGen) {
    Grid grid("../../grille_test.txt");
    Game game(1, grid);

    int initialGen = game.getCurrentGen();
    game.nextGen();

    ASSERT_EQ(initialGen + 1, game.getCurrentGen());

    // Vérifie l'état des cellules après une génération (dépend des règles du jeu)
    Cell& cell = grid.getCell(1, 1);
    ASSERT_TRUE(cell.getState());

    std::ifstream savedFile("generation_1.txt");
    ASSERT_TRUE(savedFile.is_open());

    std::string line;
    while (std::getline(savedFile, line)) {
        ASSERT_TRUE(!line.empty());
    }

    savedFile.close();
}

// // Test pour vérifier si le jeu est terminé
// TEST_CASE(TestGameIsFinished) {
//     Grid grid("../../grille_test.txt");
//     Game game(1, grid);
//
//     ASSERT_TRUE(!game.isFinished());
//
// }