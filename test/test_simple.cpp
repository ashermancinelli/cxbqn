
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



  SUBCASE("0") {
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



  SUBCASE("1") {
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



  SUBCASE("2") {
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



  SUBCASE("3") {
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



  SUBCASE("4") {
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



  SUBCASE("5") {
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



  SUBCASE("6") {
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



  SUBCASE("7") {
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



  SUBCASE("8") {
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



  SUBCASE("9") {
    CXBQN_LOG_TESTN(9);
    CompileParams p{
#include <simple_tests/t9.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    Number *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    auto ans =
#include <simple_tests/a9.hpp>
      ;
    CHECK(ans == doctest::Approx(n->v));
  }



  SUBCASE("10") {
    CXBQN_LOG_TESTN(10);
    CompileParams p{
#include <simple_tests/t10.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    Number *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    auto ans =
#include <simple_tests/a10.hpp>
      ;
    CHECK(ans == doctest::Approx(n->v));
  }



  SUBCASE("11") {
    CXBQN_LOG_TESTN(11);
    CompileParams p{
#include <simple_tests/t11.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    Number *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    auto ans =
#include <simple_tests/a11.hpp>
      ;
    CHECK(ans == doctest::Approx(n->v));
  }



  SUBCASE("12") {
    CXBQN_LOG_TESTN(12);
    CompileParams p{
#include <simple_tests/t12.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    Number *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    auto ans =
#include <simple_tests/a12.hpp>
      ;
    CHECK(ans == doctest::Approx(n->v));
  }



  SUBCASE("13") {
    CXBQN_LOG_TESTN(13);
    CompileParams p{
#include <simple_tests/t13.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    Number *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    auto ans =
#include <simple_tests/a13.hpp>
      ;
    CHECK(ans == doctest::Approx(n->v));
  }



  SUBCASE("14") {
    CXBQN_LOG_TESTN(14);
    CompileParams p{
#include <simple_tests/t14.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    Number *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    auto ans =
#include <simple_tests/a14.hpp>
      ;
    CHECK(ans == doctest::Approx(n->v));
  }



  SUBCASE("15") {
    CXBQN_LOG_TESTN(15);
    CompileParams p{
#include <simple_tests/t15.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    Number *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    auto ans =
#include <simple_tests/a15.hpp>
      ;
    CHECK(ans == doctest::Approx(n->v));
  }



  SUBCASE("16") {
    CXBQN_LOG_TESTN(16);
    CompileParams p{
#include <simple_tests/t16.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    Number *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    auto ans =
#include <simple_tests/a16.hpp>
      ;
    CHECK(ans == doctest::Approx(n->v));
  }



  SUBCASE("17") {
    CXBQN_LOG_TESTN(17);
    CompileParams p{
#include <simple_tests/t17.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    Number *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    auto ans =
#include <simple_tests/a17.hpp>
      ;
    CHECK(ans == doctest::Approx(n->v));
  }



  SUBCASE("18") {
    CXBQN_LOG_TESTN(18);
    CompileParams p{
#include <simple_tests/t18.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    Number *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    auto ans =
#include <simple_tests/a18.hpp>
      ;
    CHECK(ans == doctest::Approx(n->v));
  }



  SUBCASE("19") {
    CXBQN_LOG_TESTN(19);
    CompileParams p{
#include <simple_tests/t19.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    Number *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    auto ans =
#include <simple_tests/a19.hpp>
      ;
    CHECK(ans == doctest::Approx(n->v));
  }



}

