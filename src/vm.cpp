#include <vm.hpp>
#include <spdlog/spdlog.h>
#include <deque>
#include <sstream>

namespace cxbqn::vm {

template<typename BcType, typename StackType>
u64 _num(std::vector<BcType> &bc, uz &prog_counter, StackType &stack) {
  static constexpr u64 b{128};
  u64 n = bc[prog_counter++];
  if (n < b)
    return n;

  // wtf is this
  u64 i{1}, t{0};
  do {
    t += i * (n - b);
    i *= b;
    n = bc[prog_counter++];
  } while (n >= b);

  return t+i*n;
}

u8 vm(std::vector<i32> bc, std::vector<u64> consts, std::vector<Block> blks,
      std::vector<Body> bodies) {
  spdlog::set_pattern("cxbqn:vm:vm[%^%l%$] %v");
  spdlog::debug("enter vm");

  // VM stack
  std::deque<u64> stk;

  // program counter
  uz pc;

  auto num = [&] {
    return _num(bc, pc, stk);
  };

  auto dbg_stk = [&] {
    std::stringstream ss;
    ss << "stack:[";
    for (const auto& i : stk)
      ss << i << ",";
    ss << "]";
    spdlog::debug("{}", ss.str());
  };

  spdlog::debug("enter interpreter loop");
  while (1) {
    dbg_stk();
    switch(bc[pc++]) {
      case 0:
        stk.push_back(consts[num()]);
        break;
      default:
        spdlog::debug("unreachable code {}", bc[pc]);
        assert(false && "unreachable");
    }
  }

  return 0;
}

} // namespace cxbqn::vm
