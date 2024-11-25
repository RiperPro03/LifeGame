#include "../UnitTest.h"
#include "../../Model/Cell/Cell.h"

TEST_CASE(TestCellConstructor) {
    Cell cell(1, 2, true);
    ASSERT_EQ(1, cell.getRow());
    ASSERT_EQ(2, cell.getCol());
    ASSERT_TRUE(cell.getState());
}

TEST_CASE(TestCellDefaultState) {
    Cell cell(0, 0); // Par défaut, l'état doit être "mort"
    ASSERT_TRUE(!cell.getState());
}

TEST_CASE(TestCellSetState) {
    Cell cell(3, 4);
    cell.setState(true); // Change l'état à "vivant"
    ASSERT_TRUE(cell.getState());
    cell.setState(false); // Change l'état à "mort"
    ASSERT_TRUE(!cell.getState());
}