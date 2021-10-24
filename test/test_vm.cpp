#include <cxbqn.hpp>
#include <spdlog/spdlog.h>
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;
using namespace cxbqn::vm;

TEST_CASE("test vm", "manual input") {
  spdlog::set_level(spdlog::level::debug);
  /**
   * BQN string '5'
   *
   * cc.bqn:
   *
   * new i32_3(0,0,7),
   * new B_1(m_f64(5)),
   * new B_1(new B_3(m_f64(0),m_f64(1),m_f64(0))),
   * new B_1(new i32_2(0,0))
   *
   * cjs.bqn:
   *
   * [[0,0,7],[5],[[0,1,0]],[[0,0]]]
   */
  SECTION("manual '5'") {

    std::vector<i32> bc{0, 0, 7};

    // new B_1(m_f64(5)),
    std::vector<Value *> consts{
        new Number(5),
    };

    // B_1(new B_3(m_f64(0),m_f64(1),m_f64(0)))
    std::vector<Block> blks{Block(0, 1, 0)};

    // B_1(new i32_2(0,0))
    std::vector<Body> bodies{Body{0, 0}};

    // VM stack
    std::deque<Value *> stk;

    auto *ret = vm::vm(bc, consts, blks, bodies, stk);
    Number* n;
    CHECK(nullptr != (n = dynamic_cast<Number*>(ret)));
    CHECK(5.0 == Approx(n->v));
  }
}
