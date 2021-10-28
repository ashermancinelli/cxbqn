#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <deque>
#include <sstream>

namespace cxbqn::vm {

RunResult run(std::vector<i32> bc, std::vector<Value *> consts,
              std::vector<Block> blks, std::vector<Body> bodies) {

  CXBQN_DEBUG("vm::run:");

  debug::dbg("bc", bc);
  debug::dbg("blocks", blks);
  debug::dbg("bodies", bodies);

  std::deque<Value *> stk;

#ifdef CXBQN_DEEPCHECKS
  auto idx = blks[0].body_idx;
  if (idx >= bodies.size())
    throw std::runtime_error("body idx is greater than num bodies, something "
                             "has gone horribly wrong");
#endif

  auto body = bodies[blks[0].body_idx];

  RunResult ret;

  ret.scp = new Scope(nullptr, blks[0], body);

  ret.v = vm::vm(bc, consts, blks[0], body, stk, ret.scp);

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == ret.v)
    throw std::runtime_error("vm::run: vm returned nullptr");
#endif

  return ret;
}

Value *vm(std::vector<i32> bc, std::vector<Value *> consts, Block blk,
          Body body, std::deque<Value *> stk, Scope *scope) {

  CXBQN_DEBUG("enter vm");

  debug::dbg("bc", bc);

  // program counter
  uz pc = 0;

  debug::vdbg("consts", consts);

  i32 arga, argb;

  CXBQN_DEBUG("enter interpreter loop");

  while (1) {
    CXBQN_DEBUG("bc={},pc={}", bc[pc], pc);
    debug::vdbg("stack", stk);
    debug::scope(scope);
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
      CXBQN_DEBUG("op:VARM");
      instructions::varm(bc, pc, stk);
      break;
    case op::SETN:
      CXBQN_DEBUG("op:SETN");
      instructions::setn(stk, scope);
      break;
    case op::SETU:
      CXBQN_DEBUG("op:SETU");
      instructions::setu(stk, scope);
      break;
    case op::VARO:
    case op::VARU:
      CXBQN_DEBUG("op:VARO|VARU");
      instructions::varo(bc, pc, stk, scope);
      break;
    case op::FN1O:
    case op::FN1C:
      CXBQN_DEBUG("op:FN10|FN1C");
      instructions::fn10(bc, pc, stk, scope);
      break;
    case op::FN2O:
    case op::FN2C:
      CXBQN_DEBUG("op:FN20|FN2C");
      instructions::fn20(bc, pc, stk, scope);
      break;
    default:
      CXBQN_CRIT("unreachable code {}", bc[pc]);
      throw std::runtime_error("vm::vm: unreachable code");
    }
    pc++;
  }

  return 0;
}

} // namespace cxbqn::vm
