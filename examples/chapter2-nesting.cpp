#include "illuminate.hpp"

TEST_SUITE(A) {
  TEST_CASE(A1) {}
  TEST_SUITE(A2) {
    TEST_SUITE(A2a) {
      TEST_CASE(A2a1) {}
      TEST_CASE(A2a2) {}
      TEST_SUITE(A2a3) {}
    }
    TEST_CASE(A2b) {}
  }
}

TEST_CASE(B) {}
