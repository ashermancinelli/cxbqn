#include "instr_helpers.hpp"
namespace cxbqn::vm::instructions {

void dfnd(const ByteCodeRef bc, uz &pc, std::vector<O<Value>> &stk, observer_ptr<Scope> scp, O<Array> consts) {
  auto blk_idx = bc[++pc];

  const auto blk = scp->cu->_blocks[blk_idx];
  CXBQN_DEBUG("dfnd:pc={},block={}", pc, blk);

  if (blk.type == BlockType::func && blk.immediate) {
    auto bod = scp->cu->_bodies[blk.body_idx(0)];
    auto child = make_observer(new Scope(scp, blk_idx));
    child->vars.resize(bod.var_count+10);
    CXBQN_DEBUG("dfnd:recursing into vm");
    auto ret = vm::vm(child->cu, child, bod);
    stk.push_back(ret);
  } else {
    stk.push_back(CXBQN_NEW(BlockInst,scp, blk_idx));
  }
}
}
