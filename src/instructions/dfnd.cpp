#include "instr_helpers.hpp"
namespace cxbqn::vm::instructions {

void dfnd(const ByteCodeRef bc, uz &pc, std::vector<O<Value>> &stk, O<Scope> scp, O<Array> consts) {
  auto blk_idx = bc[++pc];

  const auto blk = scp->cu->_blocks[blk_idx];
  CXBQN_DEBUG("dfnd:pc={},block={}", pc, blk);

  if (blk.def.type == BlockType::func && blk.def.immediate) {
    auto [offset, blk_bc, nvars] = blk.body(scp->cu->_bc, scp->cu->_bodies);
    auto child = Scope::child_scope(scp, blk_idx, nvars);
    std::vector<O<Value>> stk_;

    CXBQN_DEBUG("dfnd:recursing into vm");
    auto ret = vm::vm(child->cu, blk_bc, scp->cu->_consts, stk_, child);
    stk.push_back(ret);
  } else {
    stk.push_back(make_shared<BlockInst>(scp, blk_idx, scp->cu->_consts));
  }
}
}
