#include "instr_helpers.hpp"
namespace cxbqn::vm::instructions {

void md2c(std::vector<O<Value>> &stk) {
  auto f = stk.back();
  stk.pop_back();

  auto opaque_r = stk.back();
  stk.pop_back();

  auto g = stk.back();
  stk.pop_back();

  CXBQN_DEBUG("md2c:(F _r_ G)=({} {} {})", CXBQN_STR_NC(f),
              CXBQN_STR_NC(opaque_r), CXBQN_STR_NC(g));

  auto r = dyncast<BlockInst>(opaque_r);

  if (nullptr != r and r->imm()) {
    Args a{opaque_r, f, g};
    auto v = r->call(2, a);
    stk.push_back(v);
  } else {
    stk.push_back(CXBQN_NEW(Md2Deferred,f, opaque_r, g));
  }
}

}
