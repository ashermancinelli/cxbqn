#include "instr_helpers.hpp"
namespace cxbqn::vm::instructions {

void md1c(std::vector<O<Value>> &stk) {
  auto f = stk.back();
  stk.pop_back();

  auto opaque_r = stk.back();
  stk.pop_back();

  CXBQN_DEBUG("md1c:r={},f={}", CXBQN_STR_NC(opaque_r), CXBQN_STR_NC(f));

  auto r = dyncast<BlockInst>(opaque_r);
  if (nullptr != r and r->imm()) {
    Args a{opaque_r, f, bi_Nothing()};
    auto v = r->call(1, a);
    stk.push_back(v);
  } else {
    stk.push_back(CXBQN_NEW(Md1Deferred,f, opaque_r));
  }
}

}
