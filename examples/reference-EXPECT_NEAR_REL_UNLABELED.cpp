#include "illuminate.hpp"

TEST_CASE(EXPECT_NEAR_REL_UNLABELED) {
    EXPECT_NEAR_REL_UNLABELED(2.0,4.0,1.0)
    EXPECT_NEAR_REL_UNLABELED(2.0,6.0,1.0)
    EXPECT_NEAR_REL_UNLABELED(2.0,8.0,1.0)
    EXPECT_NEAR_REL_UNLABELED(2.0,10.0,1.0)
}
