#include <cxbqn/cxbqn.hpp>
#include "utils.hpp"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;

TEST_CASE("level0") {

  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;

  SUBCASE("t0") {
    CXBQN_LOG_TESTN(0);
    CompileParams p{
#include <prim_tests/t0.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    Number *n = dynamic_cast<Number *>(ret.v);
    //REQUIRE(nullptr != n);
    //CHECK(5.0 == doctest::Approx(n->v));
  }
}
