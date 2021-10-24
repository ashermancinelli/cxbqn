#include <cxbqn.hpp>
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::vm;

TEST_CASE("test vm", "manual input") {
  /*
   * BQN string '5+5'
   *
   * cc.bqn:
   *
   * m_cai32(8,(i32[]){0,1,0,0,0,1,17,7}),
   * new B_2(inc(runtime[0]),m_f64(5)),
   * new B_1(new B_3(m_f64(0),m_f64(1),m_f64(0))),
   * new B_1(new i32_2(0,0))
   *
   * cjs.bqn:
   *
   * [[0,1,0,0,0,1,17,7],[runtime[0],5],[[0,1,0]],[[0,0]]]
   */
  SECTION("manual 5+5") {
    // m_cai32(8,(i32[]){0,1,0,0,0,1,17,7})
    std::vector<i32> bc{0,1,0,0,0,1,17,7};

    // B_2(inc(runtime[0]),m_f64(5))
    std::vector<Value*> consts;//{runtime[0], 5};

    // B_1(new B_3(m_f64(0),m_f64(1),m_f64(0)))
    std::vector<Block> blks{Block(0, 1, 0)};

    // B_1(new i32_2(0,0))
    std::vector<Body> bodies{Body{0, 0}};

    auto ret = vm::vm(bc, consts, blks, bodies);
  }
}
