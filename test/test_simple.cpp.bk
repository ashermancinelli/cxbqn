#include <cxbqn/cxbqn.hpp>
#include "utils.hpp"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;

TEST_CASE("simple") {
  const auto rt = provides::get_runtime();
  const auto runtime = rt->values;

  SUBCASE("plus") {
    CXBQN_LOG_TESTN(0);
    CompileParams p{
#include <simple_tests/t0.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    Number *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    auto ans =
#include <simple_tests/a0.hpp>
      ;
    CHECK(ans == doctest::Approx(n->v));
  }

  SUBCASE("floor, minus") {
    CXBQN_LOG_TESTN(1);
    CompileParams p{
#include <simple_tests/t1.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    Number *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    auto ans =
#include <simple_tests/a1.hpp>
      ;
    CHECK(ans == doctest::Approx(n->v));
  }

  SUBCASE("floor, minus #2") {
    CXBQN_LOG_TESTN(2);
    CompileParams p{
#include <simple_tests/t2.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    Number *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    auto ans =
#include <simple_tests/a2.hpp>
      ;
    CHECK(ans == doctest::Approx(n->v));
  }

  SUBCASE("div") {
    CXBQN_LOG_TESTN(3);
    CompileParams p{
#include <simple_tests/t3.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    Number *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    auto ans =
#include <simple_tests/a3.hpp>
      ;
    CHECK(ans == doctest::Approx(n->v));
  }

  SUBCASE("tack") {
    CXBQN_LOG_TESTN(4);
    CompileParams p{
#include <simple_tests/t4.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    Number *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    auto ans =
#include <simple_tests/a4.hpp>
      ;
    CHECK(ans == doctest::Approx(n->v));
  }

  SUBCASE("sqrt") {
    CXBQN_LOG_TESTN(5);
    CompileParams p{
#include <simple_tests/t5.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    Number *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    auto ans =
#include <simple_tests/a5.hpp>
      ;
    CHECK(ans == doctest::Approx(n->v));
  }

  SUBCASE("arith 1") {
    CXBQN_LOG_TESTN(6);
    CompileParams p{
#include <simple_tests/t6.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    Number *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    auto ans =
#include <simple_tests/a6.hpp>
      ;
    CHECK(ans == doctest::Approx(n->v));
  }

  SUBCASE("arith 2") {
    CXBQN_LOG_TESTN(7);
    CompileParams p{
#include <simple_tests/t7.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    Number *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    auto ans =
#include <simple_tests/a7.hpp>
      ;
    CHECK(ans == doctest::Approx(n->v));
  }

  SUBCASE("arith 3") {
    CXBQN_LOG_TESTN(8);
    CompileParams p{
#include <simple_tests/t8.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    Number *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    auto ans =
#include <simple_tests/a8.hpp>
      ;
    CHECK(ans == doctest::Approx(n->v));
  }
}
