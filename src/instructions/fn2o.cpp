#include "instr_helpers.hpp"
namespace cxbqn::vm::instructions {

void fn2o(std::vector<O<Value>> &stk) {
  auto w = stk.back();
  stk.pop_back();

  auto S = stk.back();
  stk.pop_back();

  auto x = stk.back();
  stk.pop_back();

  if (x->t()[t_Nothing]) {
    CXBQN_DEBUG("fn2o: got nothing for 𝕩 and 𝕨, just pushing Nothing");
    stk.push_back(bi_Nothing());
    return;
  }

  if (w->t()[t_Nothing]) {
    CXBQN_DEBUG("fn2o: got nothing for 𝕨, calling monadically");
    stk.push_back(S->call(1, {S, x, bi_Nothing()}));
    return;
  }

  CXBQN_DEBUG("fn2o: got vals for both 𝕩 and 𝕨, calling dyadically");
  auto v = S->call(2, {S, x, w});
  stk.push_back(v);
}

}
