#include "illuminate.hpp"

TEST_CASE(EXPECT_LE_UNLABELED) {
    EXPECT_LE_UNLABELED(2,3)
    EXPECT_LE_UNLABELED(2,2)
    EXPECT_LE_UNLABELED(2,1)
    EXPECT_LE_UNLABELED(2,0)
}

