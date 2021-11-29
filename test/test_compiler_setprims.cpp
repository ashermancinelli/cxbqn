#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;

TEST_CASE("Evaluate Compiler After SetPrims") {
  auto runtime = provides::get_runtime_setprims()->values;

  auto cu =
#include <cxbqn/__/c>
    ;

  auto ret = vm::run(cu);
  REQUIRE(nullptr != ret.v);
  REQUIRE(nullptr != ret.scp);
}
