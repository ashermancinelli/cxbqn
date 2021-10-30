#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <deque>
#include <sstream>

namespace cxbqn::vm {

using namespace types;

RunResult run(std::vector<i32> bc, std::vector<Value *> consts,
              std::vector<BlockDef> blk_defs, std::vector<Body> bodies) {

  CXBQN_SETLOGSTR();
  CXBQN_DEBUG("vm::run");
  CXBQN_DEBUG("bc={}", ByteCodeRef(bc));

//#ifdef CXBQN_DEEPCHECKS
//  for (const auto& b : bodies)
//    CXBQN_DEBUG("{}", b);
//#endif

  std::vector<Block> blks;

  for (auto &blkd : blk_defs)
    blks.emplace_back(bc, blkd, bodies);

  CXBQN_DEBUG("blocks={}", std::span(blks));

  std::deque<Value *> stk;

  RunResult ret;

  ret.scp = new Scope(nullptr, blks, 0);

  std::copy_n(consts.begin(), consts.size(), ret.scp->vars.begin());

  ret.v = vm::vm(bc, consts, stk, ret.scp);

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == ret.v)
    throw std::runtime_error("vm::run: vm returned nullptr");
#endif

  return ret;
}

Value *vm(ByteCodeRef bc, std::vector<Value *> consts,
          std::deque<Value *> stk, Scope *scope) {

  CXBQN_DEBUG("enter vm");

  CXBQN_DEBUG("bc={},consts={}", bc, consts);

  // program counter
  uz pc = 0;

  // debug::vdbg("consts", consts);

  i32 arga, argb;

  CXBQN_DEBUG("enter interpreter loop");

  while (1) {
    CXBQN_DEBUG("bc={},pc={},stack={},scope={}", bc[pc], pc, stk, *scope);
    switch (bc[pc]) {
    case op::PUSH:
      CXBQN_INFO("PUSH");
      stk.push_back(consts[bc[++pc]]);
      CXBQN_INFO("\t{}", bc[pc]);
      break;
    case op::RETN:
      CXBQN_INFO("RETN");
      return stk.back();
      break;
    case op::POPS:
      CXBQN_INFO("POPS");
      stk.pop_back();
      break;
    case op::VARM:
      CXBQN_INFO("VARM");
      instructions::varm(bc, pc, stk);
      break;
    case op::SETN:
      CXBQN_INFO("SETN");
      instructions::setn(stk, scope);
      break;
    case op::SETU:
      CXBQN_INFO("SETU");
      instructions::setu(stk, scope);
      break;
    case op::VARO:
    case op::VARU:
      CXBQN_INFO("VARO|VARU");
      instructions::varo(bc, pc, stk, scope);
      break;
    case op::FN1O:
    case op::FN1C:
      CXBQN_INFO("FN10|FN1C");
      instructions::fn10(bc, pc, stk);
      break;
    case op::FN2O:
    case op::FN2C:
      CXBQN_INFO("FN20|FN2C");
      instructions::fn20(bc, pc, stk);
      break;
    case op::DFND:
      CXBQN_INFO("DFND");
      instructions::dfnd(bc, pc, stk, scope);
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
