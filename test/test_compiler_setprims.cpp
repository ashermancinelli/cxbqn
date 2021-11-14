#include <cxbqn/comp_utils.hpp>
#include <cxbqn/cxbqn.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;

TEST_CASE("Evaluate Compiler After SetPrims") {
  auto runtime = provides::get_runtime_setprims()->values;

  CompileParams p2{
#include <cxbqn/__/compiled_compiler>
  };

  auto compiler_ret = vm::run(p2.bc, p2.consts.v, p2.blk_defs, p2.bodies);
  REQUIRE(nullptr != compiler_ret.v);
  REQUIRE(nullptr != compiler_ret.scp);
}
