#include "instr_helpers.hpp"
namespace cxbqn::vm::instructions {

void fn1o(std::vector<O<Value>> &stk) {
  auto S = stk.back();
  stk.pop_back();

  auto x = stk.back();
  stk.pop_back();

  if (x->t()[t_Nothing]) {
    stk.push_back(bi_Nothing());
    return;
  }

  Args a{S, x, bi_Nothing()};
  stk.push_back(S->call(1, a));
}
} // namespace cxbqn::vm::instructions
