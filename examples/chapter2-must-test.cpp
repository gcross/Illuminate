#include "illuminate.hpp"

DONT_TEST_SUITE(A) {
  MUST_TEST_CASE(A1) {}
  MUST_TEST_SUITE(A2) {
    TEST_CASE(A2a) {}
  }
}
