#include "illuminate.hpp"

TEST_CASE(ASSERT_GT_UNLABELED) {
    ASSERT_GT_UNLABELED(2,1)
    ASSERT_GT_UNLABELED(2,2)
    ASSERT_GT_UNLABELED(2,3)
}
