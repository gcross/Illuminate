#include "illuminate.hpp"

DONT_TEST_SUITE(A) {
  TEST_CASE(A1) { FAIL("This test should have been skipped!"); }
}

DONT_TEST_CASE(B) { FAIL("This test should have been skipped!"); }
