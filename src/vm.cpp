#include <cxbqn/cxbqn.hpp>
#include "vm_macros.hpp"
#include <deque>
#include <sstream>

namespace cxbqn::vm {

using namespace types;

RunResult run(std::vector<i32> bc, std::vector<Value *> consts,
              std::vector<BlockDef> blk_defs, std::vector<Body> bodies) {

  CXBQN_SETLOGSTR();
  CXBQN_DEBUG("vm::run");
  CXBQN_DEBUG("bc={}", ByteCodeRef(bc));

#ifdef CXBQN_DEEPCHECKS
  for (const auto &b : bodies)
    CXBQN_DEBUG("{}", b);
#endif

  std::vector<Block> blks;

  for (auto &blkd : blk_defs)
    blks.emplace_back(bc, blkd, bodies);

  CXBQN_DEBUG("blocks={}", std::span(blks));

  std::deque<Value *> stk;

  RunResult ret;

  ret.scp = new Scope(nullptr, blks, 0, consts);

  ret.v = vm::vm(bc, consts, stk, ret.scp);

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == ret.v)
    throw std::runtime_error("vm::run: vm returned nullptr");
#endif

  INSTR_REPORT()

  return ret;
}

Value *vm(ByteCodeRef bc, std::span<Value *> consts, std::deque<Value *> stk,
          Scope *scope) {

  CXBQN_NEWEVAL();

  CXBQN_DEBUG("bc={},consts={}", bc, consts);

  // program counter
  uz pc = 0;

  Value* ret=nullptr;

  CXBQN_DEBUG("enter interpreter loop");
  while (1) {
    CXBQN_INFO("bc={},pc={},stack={},scope={}", bc[pc], pc, stk, *scope);
    switch (bc[pc]) {
    case op::PUSH:
      INSTR1("PUSH");
      stk.push_back(consts[bc[++pc]]);
      INSTR("PUSH");
      break;
    case op::RETN:
      INSTR("RETN");
      CXBQN_DEBUG_NC("returning {}", stk.back());
      ret = stk.back();
      INSTR("RETN");
      goto done;
      break;
    case op::POPS:
      INSTR("POPS");
      stk.pop_back();
      INSTR("POPS");
      break;
    case op::VARM:
      INSTR2("VARM");
      instructions::varm(bc, pc, stk);
      INSTR("VARM");
      break;
    case op::SETN:
      INSTR("SETN");
      instructions::setn(stk, scope);
      INSTR("SETN");
      break;
    case op::SETU:
      INSTR("SETU");
      instructions::setu(stk, scope);
      INSTR("SETU");
      break;
    case op::VARU:
    case op::VARO:
      INSTR2("VARO");
      instructions::varo(bc, pc, stk, scope);
      INSTR("VARO");
      break;
    case op::FN1C:
      INSTR("FN1C");
      instructions::fn10(bc, pc, stk);
      INSTR("FN1C");
      break;
    case op::FN2C:
      INSTR("FN2C");
      instructions::fn20(bc, pc, stk);
      INSTR("FN2C");
      break;
    case op::DFND:
      INSTR1("DFND");
      instructions::dfnd(bc, pc, stk, scope);
      INSTR("DFND");
      break;
    case op::ARRO:
      INSTR1("ARRO");
      instructions::arro(bc, pc, stk);
      INSTR("ARRO");
      break;
    case op::ARRM:
      INSTR1("ARRM");
      instructions::arrm(bc, pc, stk);
      INSTR("ARRM");
      break;
    case op::MD1C:
      INSTR("MD1C");
      instructions::md1c(bc, pc, stk, scope);
      INSTR("MD1C");
      break;
    case op::MD2C:
      INSTR("MD2C");
      instructions::md2c(bc, pc, stk, scope);
      INSTR("MD2C");
      break;
    case op::TR2D:
      INSTR("TR2D");
      instructions::tr2d(bc, pc, stk, scope);
      INSTR("TR2D");
      break;
    case op::TR3D:
      INSTR("TR3D");
      instructions::tr3d(bc, pc, stk, scope);
      INSTR("TR3D");
      break;
    case op::SETM:
      INSTR("SETM");
      instructions::setm(stk, scope);
      INSTR("SETM");
      break;
    case op::SETC:
      INSTR("SETC");
      instructions::setc(stk, scope);
      INSTR("SETC");
      break;
    default:
      CXBQN_CRIT("unreachable code {}", bc[pc]);
      throw std::runtime_error("vm::vm: unreachable code");
    }
    pc++;
  }

done:

  CXBQN_ENDEVAL();

  return ret;
}

#undef INSTR
#undef INSTR1
#undef INSTR2

} // namespace cxbqn::vm
