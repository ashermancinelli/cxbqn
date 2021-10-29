#include <cxbqn/cxbqn.hpp>
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <spdlog/spdlog.h>

#include "utils.hpp"

using namespace cxbqn;
using namespace cxbqn::vm;
using namespace cxbqn::types;
using namespace cxbqn::provides;


TEST_CASE("Bytecode", "") {

  spdlog::set_level(spdlog::level::debug);

  SECTION("manual bc t0") {
    spdlog::debug("t0");
    CompileParams p{
#include <bc_tests/t0.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);

    Number* n = dynamic_cast<Number*>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(5.0 == Approx(n->v));
  }

  SECTION("manual bc t1") {
    spdlog::debug("t1");
    CompileParams p{
#include <bc_tests/t1.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);

    Number* n = dynamic_cast<Number*>(ret.v);;
    REQUIRE(nullptr != n);
    CHECK(3.0 == Approx(n->v));
  }

  SECTION("manual bc t2") {
    spdlog::debug("t2");
    CompileParams p{
#include <bc_tests/t2.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);

    Reference* r = dynamic_cast<Reference*>(ret.v);
    REQUIRE(nullptr != r);
    REQUIRE(nullptr != ret.scp);

    Value *v = ret.scp->get(r);
    REQUIRE(nullptr != v);
    auto *n = dynamic_cast<Number*>(v);
    REQUIRE(nullptr != n);
    CHECK(5.0 == Approx(n->v));
  }

  SECTION("manual bc t3") {
    spdlog::debug("t3");
    CompileParams p{
#include <bc_tests/t3.hpp>
    };

    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.scp);
    REQUIRE(nullptr != ret.v);
    auto *scp = ret.scp;
    auto* r = dynamic_cast<Reference*>(ret.v);
    REQUIRE(nullptr != r);
    auto *v = scp->get(r);
    REQUIRE(nullptr != v);
    auto *n = dynamic_cast<Number*>(v);
    REQUIRE(nullptr != n);
    CHECK(4.0 == Approx(n->v));
  }

  SECTION("manual bc t4") {
    spdlog::debug("t4");
    CompileParams p{
#include <bc_tests/t4.hpp>
    };
    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.scp);
    REQUIRE(nullptr != ret.v);
    auto* n = dynamic_cast<Number*>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(2.0 == Approx(n->v));
  }

  SECTION("manual bc t5") {
    spdlog::debug("t5");
    CompileParams p{
#include <bc_tests/t5.hpp>
    };
    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.scp);
    REQUIRE(nullptr != ret.v);
    auto* n = dynamic_cast<Number*>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(1.0 == Approx(n->v));
  }

  SECTION("manual bc t6") {
    spdlog::debug("t6");
    CompileParams p{
#include <bc_tests/t6.hpp>
    };
    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.scp);
    REQUIRE(nullptr != ret.v);
    auto* n = dynamic_cast<Number*>(ret.v);
    REQUIRE(nullptr != n);
    CHECK(2.0 == Approx(n->v));
  }

  SECTION("manual bc t7") {
    spdlog::debug("t7");
    CompileParams p{
#include <bc_tests/t7.hpp>
    };
    auto ret = vm::run(p.bc, p.consts.v, p.blk_defs, p.bodies);
    REQUIRE(nullptr != ret.scp);
    REQUIRE(nullptr != ret.v);
    //auto* n = dynamic_cast<Number*>(ret.v);
    //REQUIRE(nullptr != n);
    //CHECK(6.0 == Approx(n->v));
  }
}
