#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <spdlog/spdlog.h>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "utils.hpp"

using namespace cxbqn;
using namespace cxbqn::vm;
using namespace cxbqn::types;
using namespace cxbqn::provides;

TEST_CASE("bc0-9") {
  CXBQN_SETLOGSTR();

  SUBCASE("t0") {
    CXBQN_LOG_TESTN(0);
    CompileParams p{
#include <bc_tests/t0.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);

    Number *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(5.0 == doctest::Approx(n->v));
  }

  SUBCASE("t1") {
    CXBQN_LOG_TESTN(1);
    CompileParams p{
#include <bc_tests/t1.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);

    Number *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(3.0 == doctest::Approx(n->v));
  }

  SUBCASE("t2") {
    CXBQN_LOG_TESTN(2);
    CompileParams p{
#include <bc_tests/t2.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);

    REQUIRE(nullptr != ret.v);
    REQUIRE(nullptr != ret.scp);
    Number *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(5.0 == doctest::Approx(n->v));
  }

  SUBCASE("t3") {
    CXBQN_LOG_TESTN(3);
    CompileParams p{
#include <bc_tests/t3.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.scp);
    REQUIRE(nullptr != ret.v);
    auto *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(4.0 == doctest::Approx(n->v));
  }

  SUBCASE("t4") {
    CXBQN_LOG_TESTN(4);
    CompileParams p{
#include <bc_tests/t4.hpp>
    };
    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.scp);
    REQUIRE(nullptr != ret.v);
    auto *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(2.0 == doctest::Approx(n->v));
  }

  SUBCASE("t5") {
    CXBQN_LOG_TESTN(5);
    CompileParams p{
#include <bc_tests/t5.hpp>
    };
    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.scp);
    REQUIRE(nullptr != ret.v);
    auto *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(1.0 == doctest::Approx(n->v));
  }

  SUBCASE("t6") {
    CXBQN_LOG_TESTN(6);
    CompileParams p{
#include <bc_tests/t6.hpp>
    };
    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.scp);
    REQUIRE(nullptr != ret.v);
    auto *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(2.0 == doctest::Approx(n->v));
  }

  SUBCASE("t7") {
    CXBQN_LOG_TESTN(7);
    CompileParams p{
#include <bc_tests/t7.hpp>
    };
    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.scp);
    REQUIRE(nullptr != ret.v);
    auto *n = dynamic_cast<Number *>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(6.0 == doctest::Approx(n->v));
  }

  /*  A←{𝕨}⋄3 A 4           #    dyadic block function
   * {1,1,33,0,0,48,6,0,1,34,0,0,0,0,17,7,34,0,2,7},
   * {3,4},
   * {{0,1,0},{0,0,{{},{1}}}},
   * {{0,1},{16,3}}
   */
  SUBCASE("t8") {
    CXBQN_LOG_TESTN(8);
    CompileParams p{
#include <bc_tests/t8.hpp>
    };
    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.scp);
    REQUIRE(nullptr != ret.v);
    auto* n = dynamic_cast<Number*>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(3.0 == doctest::Approx(n->v));
  }

  /*  a‿b←7‿2⋄a             # 11 ARRO, 12 ARRM
   * {0,0,0,1,11,2,33,0,0,33,0,1,12,2,48,6,34,0,0,7},
   * {7,2},
   * {{0,1,0}},
   * {{0,2}} 
   */
  SUBCASE("t9") {
    CXBQN_LOG_TESTN(9);
    CompileParams p{
#include <bc_tests/t9.hpp>
    };
    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.scp);
    REQUIRE(nullptr != ret.v);
    auto* n = dynamic_cast<Number*>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(7.0 == doctest::Approx(n->v));
  }
}

TEST_CASE("t10") {
  CXBQN_LOG_TESTN(10);
  CompileParams p{
#include <bc_tests/t10.hpp>
  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.scp);
  REQUIRE(nullptr != ret.v);
  auto* n = dynamic_cast<Number*>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(4.0 == doctest::Approx(n->v));
}

TEST_CASE("t11") {
  CXBQN_LOG_TESTN(11);
  CompileParams p{
#include <bc_tests/t11.hpp>
  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.scp);
  REQUIRE(nullptr != ret.v);
  auto* n = dynamic_cast<Number*>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(6.0 == doctest::Approx(n->v));
}

TEST_CASE("t12") {
  CXBQN_LOG_TESTN(12);
  CompileParams p{
#include <bc_tests/t12.hpp>
  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.scp);
  REQUIRE(nullptr != ret.v);
  auto* n = dynamic_cast<Number*>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1.0 == doctest::Approx(n->v));
}

TEST_CASE("t13") {
  CXBQN_LOG_TESTN(13);
  CompileParams p{
#include <bc_tests/t13.hpp>
  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.scp);
  REQUIRE(nullptr != ret.v);
  auto* n = dynamic_cast<Number*>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(2.0 == doctest::Approx(n->v));
}

TEST_CASE("t14") {
  CXBQN_LOG_TESTN(14);
  CompileParams p{
#include <bc_tests/t14.hpp>
  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.scp);
  REQUIRE(nullptr != ret.v);
  auto* n = dynamic_cast<Number*>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(3.0 == doctest::Approx(n->v));
}

TEST_CASE("t15") {
  CXBQN_LOG_TESTN(15);
  CompileParams p{
#include <bc_tests/t15.hpp>
  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.scp);
  REQUIRE(nullptr != ret.v);
  auto* n = dynamic_cast<Number*>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(4.0 == doctest::Approx(n->v));
}

TEST_CASE("t16") {
  CXBQN_LOG_TESTN(16);
  CompileParams p{
#include <bc_tests/t16.hpp>
  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.scp);
  REQUIRE(nullptr != ret.v);
  auto* n = dynamic_cast<Number*>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(2.0 == doctest::Approx(n->v));
}

TEST_CASE("t17") {
  CXBQN_LOG_TESTN(17);
  CompileParams p{
#include <bc_tests/t17.hpp>
  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.scp);
  REQUIRE(nullptr != ret.v);
  auto* n = dynamic_cast<Number*>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(2.0 == doctest::Approx(n->v));
}

TEST_CASE("t18") {
  CXBQN_LOG_TESTN(18);
  CompileParams p{
#include <bc_tests/t18.hpp>
  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.scp);
  REQUIRE(nullptr != ret.v);
  auto* n = dynamic_cast<Number*>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(8.0 == doctest::Approx(n->v));
}

TEST_CASE("t19") {
  CXBQN_LOG_TESTN(19);
  CompileParams p{
#include <bc_tests/t19.hpp>
  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.scp);
  REQUIRE(nullptr != ret.v);
  auto* n = dynamic_cast<Number*>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(5.0 == doctest::Approx(n->v));
}

TEST_CASE("t20") {
  CXBQN_LOG_TESTN(20);
  CompileParams p{
#include <bc_tests/t20.hpp>
  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.scp);
  REQUIRE(nullptr != ret.v);
  auto* n = dynamic_cast<Number*>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1.0 == doctest::Approx(n->v));
}

TEST_CASE("t21") {
  CXBQN_LOG_TESTN(21);
  CompileParams p{
#include <bc_tests/t21.hpp>
  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.scp);
  REQUIRE(nullptr != ret.v);
  auto* n = dynamic_cast<Number*>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(4.0 == doctest::Approx(n->v));
}

TEST_CASE("t22") {
  CXBQN_LOG_TESTN(22);
  CompileParams p{
#include <bc_tests/t22.hpp>
  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.scp);
  REQUIRE(nullptr != ret.v);
  auto* n = dynamic_cast<Number*>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1.0 == doctest::Approx(n->v));
}

TEST_CASE("t23") {
  CXBQN_LOG_TESTN(23);
  CompileParams p{
#include <bc_tests/t23.hpp>
  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.scp);
  REQUIRE(nullptr != ret.v);
  auto* n = dynamic_cast<Number*>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(2.0 == doctest::Approx(n->v));
}

TEST_CASE("t24") {
  CXBQN_LOG_TESTN(24);
  CompileParams p{
#include <bc_tests/t24.hpp>
  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.scp);
  REQUIRE(nullptr != ret.v);
  auto* n = dynamic_cast<Number*>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(6.0 == doctest::Approx(n->v));
}

TEST_CASE("t25") {
  CXBQN_LOG_TESTN(25);
  CompileParams p{
#include <bc_tests/t25.hpp>
  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.scp);
  REQUIRE(nullptr != ret.v);
  auto* n = dynamic_cast<Number*>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(5.0 == doctest::Approx(n->v));
}

TEST_CASE("t26") {
  CXBQN_LOG_TESTN(26);
  CompileParams p{
#include <bc_tests/t26.hpp>
  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.scp);
  REQUIRE(nullptr != ret.v);
  auto* n = dynamic_cast<Number*>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(3.0 == doctest::Approx(n->v));
}

TEST_CASE("t27") {
  CXBQN_LOG_TESTN(27);
  CompileParams p{
#include <bc_tests/t27.hpp>
  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.scp);
  REQUIRE(nullptr != ret.v);
  auto* n = dynamic_cast<Number*>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(1.0 == doctest::Approx(n->v));
}

TEST_CASE("t28") {
  CXBQN_LOG_TESTN(28);
  CompileParams p{
#include <bc_tests/t28.hpp>
  };
  auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
  REQUIRE(nullptr != ret.scp);
  REQUIRE(nullptr != ret.v);
  auto* n = dynamic_cast<Number*>(ret.v);
  REQUIRE(nullptr != n);
  CHECK(2.0 == doctest::Approx(n->v));
}
