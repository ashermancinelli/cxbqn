#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <spdlog/spdlog.h>

#include "utils.hpp"

using namespace cxbqn;
using namespace cxbqn::vm;
using namespace cxbqn::types;
using namespace cxbqn::provides;

TEST_CASE("bc0-9", "") {
  CXBQN_SETLOGSTR();

  SECTION("t0") {
    CXBQN_LOG_TESTN(0);
    CompileParams p{
#include <bc_tests/t0.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);

    Number *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(5.0 == Approx(n->v));
  }

  SECTION("t1") {
    CXBQN_LOG_TESTN(1);
    CompileParams p{
#include <bc_tests/t1.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);

    Number *n = dynamic_cast<Number *>(ret.v);
    ;
    REQUIRE(nullptr != n);
    CHECK(3.0 == Approx(n->v));
  }

  SECTION("t2") {
    CXBQN_LOG_TESTN(2);
    CompileParams p{
#include <bc_tests/t2.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);

    Reference *r = dynamic_cast<Reference *>(ret.v);
    REQUIRE(nullptr != r);
    REQUIRE(nullptr != ret.scp);

    Value *v = ret.scp->get(r);
    REQUIRE(nullptr != v);
    auto *n = dynamic_cast<Number *>(v);
    REQUIRE(nullptr != n);
    CHECK(5.0 == Approx(n->v));
  }

  SECTION("t3") {
    CXBQN_LOG_TESTN(3);
    CompileParams p{
#include <bc_tests/t3.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.scp);
    REQUIRE(nullptr != ret.v);
    auto *scp = ret.scp;
    auto *r = dynamic_cast<Reference *>(ret.v);
    REQUIRE(nullptr != r);
    auto *v = scp->get(r);
    REQUIRE(nullptr != v);
    auto *n = dynamic_cast<Number *>(v);
    REQUIRE(nullptr != n);
    CHECK(4.0 == Approx(n->v));
  }

  SECTION("t4") {
    CXBQN_LOG_TESTN(4);
    CompileParams p{
#include <bc_tests/t4.hpp>
    };
    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.scp);
    REQUIRE(nullptr != ret.v);
    auto *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(2.0 == Approx(n->v));
  }

  SECTION("t5") {
    CXBQN_LOG_TESTN(5);
    CompileParams p{
#include <bc_tests/t5.hpp>
    };
    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.scp);
    REQUIRE(nullptr != ret.v);
    auto *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(1.0 == Approx(n->v));
  }

  SECTION("t6") {
    CXBQN_LOG_TESTN(6);
    CompileParams p{
#include <bc_tests/t6.hpp>
    };
    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.scp);
    REQUIRE(nullptr != ret.v);
    auto *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(2.0 == Approx(n->v));
  }

  SECTION("t7") {
    CXBQN_LOG_TESTN(7);
    CompileParams p{
#include <bc_tests/t7.hpp>
    };
    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.scp);
    REQUIRE(nullptr != ret.v);
    auto *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(6.0 == Approx(n->v));
  }

  /*  A←{𝕨}⋄3 A 4           #    dyadic block function
   * {1,1,33,0,0,48,6,0,1,34,0,0,0,0,17,7,34,0,2,7},
   * {3,4},
   * {{0,1,0},{0,0,{{},{1}}}},
   * {{0,1},{16,3}}
   */
  SECTION("t8") {
    CXBQN_LOG_TESTN(8);
    CompileParams p{
#include <bc_tests/t8.hpp>
    };
    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.scp);
    REQUIRE(nullptr != ret.v);
    auto* n = dynamic_cast<Number*>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(3.0 == Approx(n->v));
  }

  /*  a‿b←7‿2⋄a             # 11 ARRO, 12 ARRM
   * {0,0,0,1,11,2,33,0,0,33,0,1,12,2,48,6,34,0,0,7},
   * {7,2},
   * {{0,1,0}},
   * {{0,2}} 
   */
  SECTION("t9") {
    CXBQN_LOG_TESTN(9);
    CompileParams p{
#include <bc_tests/t9.hpp>
    };
    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.scp);
    REQUIRE(nullptr != ret.v);
    auto* n = dynamic_cast<Number*>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(7.0 == Approx(n->v));
  }
}

TEST_CASE("bc10-19", "") {
  SECTION("t10") {
    CXBQN_LOG_TESTN(10);
    CompileParams p{
#include <bc_tests/t10.hpp>
    };
    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.scp);
    REQUIRE(nullptr != ret.v);
    auto* n = dynamic_cast<Number*>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(4.0 == Approx(n->v));
  }

  SECTION("t11") {
    CXBQN_LOG_TESTN(11);
    CompileParams p{
#include <bc_tests/t11.hpp>
    };
    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.scp);
    REQUIRE(nullptr != ret.v);
    auto* n = dynamic_cast<Number*>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(6.0 == Approx(n->v));
  }

  SECTION("t12") {
    CXBQN_LOG_TESTN(12);
    CompileParams p{
#include <bc_tests/t12.hpp>
    };
    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.scp);
    REQUIRE(nullptr != ret.v);
    auto* n = dynamic_cast<Number*>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(1.0 == Approx(n->v));
  }

  SECTION("t13") {
    CXBQN_LOG_TESTN(13);
    CompileParams p{
#include <bc_tests/t13.hpp>
    };
    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.scp);
    REQUIRE(nullptr != ret.v);
    auto* n = dynamic_cast<Number*>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(2.0 == Approx(n->v));
  }
}
