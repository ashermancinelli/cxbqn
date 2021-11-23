#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <unistd.h>
#include <utf8.h>

namespace cxbqn::types {

BlockInst::BlockInst(O<Scope> scp, uz blk_idx, O<Array> consts)
    : scp{scp}, blk_idx{blk_idx}, consts{consts} {
  // In the specification, the return of •Type for a function, 1mod, and 2mod
  // are 3, 4, and 5, but the block types as returned from the compiler are
  // either 0, 1, or 2. That's why we have this offset.
  type = static_cast<u32>(scp->cu->_blocks[this->blk_idx].def.type) + 3;
}

bool BlockInst::imm() const {
  return this->scp->cu->_blocks[this->blk_idx].def.immediate;
}

O<Value> BlockInst::call(u8 nargs, std::vector<O<Value>> args) {

#ifdef CXBQN_DEEPCHECKS
  if ((1 == nargs) != (args[2]->t()[t_Nothing]))
    throw std::runtime_error(
        "BlockInst: got · for 𝕨 with 2 args, or non-· with 1 arg");
#endif

  const auto blk = scp->cu->_blocks[blk_idx];

  auto [offset, bc, nvars] = blk.body(scp->cu->_bc, scp->cu->_bodies, nargs);

  auto child = Scope::child_scope(scp, blk_idx, std::max(nvars, args.size()));
  std::copy(args.begin(), args.end(), child->vars.begin());

  CXBQN_DEBUG("BlockInst::call:nargs={},childscope={},blk={}", args.size(),
              *child, blk);

  std::vector<O<Value>> stk;

#ifdef CXBQN_STACKTRACE_DEEP
  try {
#endif
    auto cu = scp->cu;
    CXBQN_DEBUG("BlockInst::call:recursing into vm");
    auto ret = vm::vm(cu, bc, cu->_consts, stk, child);
    CXBQN_DEBUG("BlockInst::call:returning {}", CXBQN_STR_NC(ret));
    return ret;
#ifdef CXBQN_STACKTRACE_DEEP
  } catch (std::runtime_error &e) {
    if (!child->has_source_info())
      throw;
    std::stringstream ss;
    ss << e.what() << "\n";
    child->source_for_program_counter(offset, ss);
    throw std::runtime_error(ss.str());
  }
#endif
}

} // namespace cxbqn::types
