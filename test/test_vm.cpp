#include <cxbqn.hpp>
#include <spdlog/spdlog.h>
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "utils.hpp"

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;
using namespace cxbqn::vm;

TEST_CASE("test vm", "manual input") {
  spdlog::set_level(spdlog::level::debug);

  /**
   * BQN string '5'
   *
   * cjs.bqn:
   *
   * [[0,0,7],[5],[[0,1,0]],[[0,0]]]
   */
  SECTION("manual '5'") {

    struct CompileParams p{
      {0,0,7}, // i32_3(0,0,7)
      {5}, // B_1(m_f64(5)),
      {{0,1,0}}, // B_1(B_3(m_f64(0),m_f64(1),m_f64(0)))
      {{0,0}} // B_1(i32_2(0,0))
    };

    std::deque<Value *> stk;

    auto* sc = new Scope();

    auto *ret = vm::vm(p.bc, p.consts.v, p.blks, p.bodies, stk, sc);

    Number* n;
    CHECK(nullptr != (n = dynamic_cast<Number*>(ret)));
    CHECK(5.0 == Approx(n->v));
  }
}
