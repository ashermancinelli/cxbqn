
#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <unistd.h>
#include <utf8.h>

namespace cxbqn::types {

bool BlockInst::imm() const {
  return this->scp->blks[this->blk_idx].def.immediate;
}

O<Value> BlockInst::call(u8 nargs, std::vector<O<Value>> args) {

  const auto blk = scp->blks[blk_idx];

  auto *child = new Scope(scp, blk_idx, scp->blks);

  auto [bc, nvars] = blk.body(child->bc(), nargs);
  std::copy(args.begin(), args.end(), child->vars.begin());

  CXBQN_DEBUG("BlockInst::call:nargs={},childscope={},blk={}", args.size(),
              *child, blk);

  std::vector<O<Value>> stk;

  CXBQN_DEBUG("BlockInst::call:recursing into vm");
  auto ret = vm::vm(bc, child->consts(), stk, child);
  CXBQN_DEBUG("BlockInst::call:returning {}", CXBQN_STR_NC(ret));

  return ret;
}

}
