#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <unistd.h>
#include <utf8.h>

namespace cxbqn::types {

bool BlockInst::imm() const {
  return this->scp->blocks()[this->blk_idx].def.immediate;
}

O<Value> BlockInst::call(u8 nargs, std::vector<O<Value>> args) {

#ifdef CXBQN_DEEPCHECKS
  if ((1 == nargs) != (args[2]->t()[t_Nothing]))
    throw std::runtime_error("BlockInst: got · for 𝕨 with 2 args, or non-· with 1 arg");
#endif

  const auto blk = scp->blocks()[blk_idx];

  auto child = Scope::child_scope(scp, blk_idx);

  auto [offset, bc, nvars] = blk.body(child->bc(), child->bodies(), nargs);
  std::copy(args.begin(), args.end(), child->vars.begin());

  CXBQN_DEBUG("BlockInst::call:nargs={},childscope={},blk={}", args.size(),
              *child, blk);

  std::vector<O<Value>> stk;

#ifdef CXBQN_STACKTRACE_DEEP
  try {
#endif
    CXBQN_DEBUG("BlockInst::call:recursing into vm");
    auto ret = vm::vm(bc, child->consts(), stk, child);
    CXBQN_DEBUG("BlockInst::call:returning {}", CXBQN_STR_NC(ret));
    return ret;
#ifdef CXBQN_STACKTRACE_DEEP
  } catch (std::runtime_error &e) {
    std::stringstream ss;
    ss << e.what() << "\n";
    child->source_for_program_counter(offset, ss);
    throw std::runtime_error(ss.str());
  }
#endif
}

} // namespace cxbqn::types
