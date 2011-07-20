#include "illuminate.hpp"

TEST_CASE(approximate_equality_test) {
    EXPECT_NEAR_ABS_LABELED("",4,"",4.2,0.1)
    EXPECT_NEAR_REL_LABELED("",4,"",4.2,0.1)
    EXPECT_NEAR_ABS_LABELED("",0.1,"",0.12,0.1)
    EXPECT_NEAR_REL_LABELED("",0.1,"",0.12,0.1)
    EXPECT_NEAR_ABS_LABELED("",0.01,"",0.012,0.1)
    EXPECT_NEAR_REL_LABELED("",0.01,"",0.012,0.1)
}
