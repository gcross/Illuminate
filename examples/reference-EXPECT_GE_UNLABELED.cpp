#include "illuminate.hpp"

TEST_CASE(EXPECT_GE_UNLABELED) {
    EXPECT_GE_UNLABELED(1,0)
    EXPECT_GE_UNLABELED(1,1)
    EXPECT_GE_UNLABELED(1,2)
    EXPECT_GE_UNLABELED(1,3)
}