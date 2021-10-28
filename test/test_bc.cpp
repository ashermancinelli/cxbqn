#include <cxbqn.hpp>
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
    CompileParams p{
#include <bc_tests/t0.hpp>
    };

    std::deque<Value *> stk;

    auto* sc = new Scope();

    auto *ret = vm::vm(p.bc, p.consts.v, p.blks, p.bodies, stk, sc);
    Number* n;
    REQUIRE(nullptr != (n = dynamic_cast<Number*>(ret)));
    CHECK(5.0 == Approx(n->v));
    delete sc;
  }

  SECTION("manual bc t1") {
    CompileParams p{
#include <bc_tests/t1.hpp>
    };

    std::deque<Value *> stk;

    auto* sc = new Scope();

    auto *ret = vm::vm(p.bc, p.consts.v, p.blks, p.bodies, stk, sc);
    Number* n;
    REQUIRE(nullptr != (n = dynamic_cast<Number*>(ret)));
    CHECK(3.0 == Approx(n->v));
    delete sc;
  }

  SECTION("manual bc t2") {
    CompileParams p{
#include <bc_tests/t2.hpp>
    };

    std::deque<Value *> stk;

    auto* sc = new Scope();

    auto *ret = vm::vm(p.bc, p.consts.v, p.blks, p.bodies, stk, sc);
    Number* n;
    REQUIRE(nullptr != (n = dynamic_cast<Number*>(ret)));
    CHECK(5.0 == Approx(n->v));
    delete sc;
  }
}
