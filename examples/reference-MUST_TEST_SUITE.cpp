#include "illuminate.hpp"

DONT_TEST_SUITE(Parent) {
  MUST_TEST_SUITE(Child) {
    TEST_CASE(Grandchild) {}
  }
}
