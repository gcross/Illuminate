#include "illuminate.hpp"

TEST_SUITE(Parent) {
  TEST_CASE(Child1) {}
  TEST_SUITE(Child2) {
    TEST_SUITE(Grandchild21) {
      TEST_CASE(Greatgrandchild211) {}
      TEST_SUITE(Greatgrandchild212) {}
    }
    TEST_CASE(Grandchild22) {}
  }
}
