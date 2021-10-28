#include <cxbqn.hpp>
#include <deque>
#include <cxbqn_debug.hpp>
#include <sstream>

namespace cxbqn::vm {

template <typename BcType, typename StackType>
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

  return t + i * n;
}

Value *vm(std::vector<i32> bc, std::vector<Value *> consts,
          std::vector<Block> blks, std::vector<Body> bodies,
          std::deque<Value *> stk, Scope* scope) {
  CXBQN_DEBUG("enter vm");

  debug::dbg("bc", bc);
  debug::dbg("blocks", blks);
  debug::dbg("bodies", bodies);

  // program counter
  uz pc = 0;

  // this is very expensive
  debug::vdbg("consts", consts);

  i32 arga, argb;

  CXBQN_DEBUG("enter interpreter loop");
  while (1) {
    CXBQN_DEBUG("bc={},pc={}", bc[pc], pc);
    debug::vdbg("stack", stk);
    switch (bc[pc]) {
    case op::PUSH:
      pc++;
      CXBQN_DEBUG("op:PUSH bc[pc++]={}", bc[pc]);
      stk.push_back(consts[bc[pc]]);
      break;
    case op::RETN:
      CXBQN_DEBUG("op:RETN");
      return stk.back();
      break;
    case op::POPS:
      CXBQN_DEBUG("op:POPS");
      stk.pop_back();
      break;
    case op::VARM:
      arga = bc[++pc];
      argb = bc[++pc];
      CXBQN_DEBUG("op:VARM:a={},b={}", arga, argb);
      stk.push_back(new types::Reference(
          /*depth=*/static_cast<uz>(arga),
          /*position in parent=*/static_cast<uz>(argb)));
      break;
    case op::SETN:
      CXBQN_DEBUG("op:SETN");
      instructions::setn(stk, scope);
      break;
    default:
      CXBQN_CRIT("unreachable code {}", bc[pc]);
      throw std::runtime_error("cxbqn::vim::vim: unreachable code");
    }
    pc++;
  }

  return 0;
}

} // namespace cxbqn::vm
