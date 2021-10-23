#include <cxbqn.hpp>
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("test types", "Array") {
  using namespace cxbqn;
  using namespace cxbqn::types;

  SECTION("Array Constructor (sizes, values)") {
    auto* ar = new Array({3}, {1, 2, 3});
    CHECK(ar->shape.front() == 3);
    auto it = ar->values;
    CHECK(*it++ == 1);
    CHECK(*it++ == 2);
    CHECK(*it++ == 3);
    CHECK(it == (3+ar->values));
    delete ar;
  }

  SECTION("Array Constructor (values)") {
    auto* ar = new Array({1, 2, 3});
    CHECK(ar->shape.front() == 3);
    auto it = ar->values;
    CHECK(*it++ == 1);
    CHECK(*it++ == 2);
    CHECK(*it++ == 3);
    CHECK(it == (3+ar->values));
    delete ar;
  }

  SECTION("Array Constructor ()") {
    auto* ar = new Array<u8>();
    CHECK(ar->shape.empty());
    CHECK(ar->values == nullptr);
    delete ar;
  }

}
