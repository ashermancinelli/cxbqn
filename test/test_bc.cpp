#include <cxbqn.hpp>
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "utils.hpp"

using namespace cxbqn;
using namespace cxbqn::vm;
using namespace cxbqn::types;
using namespace cxbqn::provides;

TEST_CASE("Bytecode", "") {
  SECTION("manual bc t0") {
    CompileParams p{
#include <bc_tests/t0.hpp>
    };

    std::deque<Value *> stk;

    auto *ret = vm::vm(p.bc, p.consts.v, p.blks, p.bodies, stk);
    Number* n;
    CHECK(nullptr != (n = dynamic_cast<Number*>(ret)));
    CHECK(5.0 == Approx(n->v));
  }
}
