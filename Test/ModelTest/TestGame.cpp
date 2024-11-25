#include "../UnitTest.h"
#include "../../Model/Game/Game.h"
#include "../../Model/Grid/Grid.h"

// TEST_CASE(TestGameConstructor) {
//     Grid grid("test_grid.txt");
//     Game game(1, grid);
//
//     ASSERT_EQ(1, game.getCurrentGen());
// }
//
// TEST_CASE(TestGameNextGen) {
//     Grid grid("test_grid.txt");
//     Game game(1, grid);
//
//     int initialGen = game.getCurrentGen();
//     game.nextGen();
//     ASSERT_EQ(initialGen + 1, game.getCurrentGen());
// }
//
// TEST_CASE(TestGameIsFinished) {
//     Grid grid("test_grid.txt");
//     Game game(1, grid);
//
//     ASSERT_TRUE(!game.isFinished());
// }