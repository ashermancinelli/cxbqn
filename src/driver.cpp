#include <cxbqn.hpp>
#include <spdlog/spdlog.h>

using namespace cxbqn;
using namespace cxbqn::types;
using namespace cxbqn::provides;
using namespace cxbqn::vm;

int main(int argc, char **argv) {
  spdlog::set_pattern("cxbqn:driver[%^%l%$] %v");
  spdlog::set_level(spdlog::level::debug);
  spdlog::debug("create bc, consts, blks, bodies");

  // m_cai32(8,(i32[]){0,1,0,0,0,1,17,7})
  std::vector<i32> bc{0, 1, 0, 0, 0, 1, 17, 7};

  // B_2(inc(runtime[0]),m_f64(5))
  std::vector<Value *> consts{
      new Type(),
      new Number(5),
  }; //{runtime[0], 5};

  // B_1(new B_3(m_f64(0),m_f64(1),m_f64(0)))
  std::vector<Block> blks{Block(0, 1, 0)};

  // B_1(new i32_2(0,0))
  std::vector<Body> bodies{Body{0, 0}};

  std::deque<Value*> stk;

  spdlog::debug("run vm");
  auto* ret = vm::vm(bc, consts, blks, bodies, stk);

  spdlog::debug("cleanup");
  return 0;
}
