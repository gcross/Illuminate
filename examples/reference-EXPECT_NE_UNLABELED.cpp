#include "illuminate.hpp"

TEST_CASE(EXPECT_NE_UNLABELED) {
    EXPECT_NE_UNLABELED(1,2)
    EXPECT_NE_UNLABELED(1,1)
    EXPECT_NE_UNLABELED(0,0)
}
