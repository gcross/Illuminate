#include "illuminate.hpp"

DONT_TEST_SUITE(Parent) {
  TEST_CASE(Child1) { FAIL("This test should have been skipped!"); }
  TEST_SUITE(Child2) {
    TEST_CASE(Grandchild) { FAIL("This test should have been skipped!"); }
  }
}
