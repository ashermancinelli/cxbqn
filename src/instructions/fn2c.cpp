#include "instr_helpers.hpp"
namespace cxbqn::vm::instructions {

void fn2c(std::vector<O<Value>> &stk) {
  auto w = stk.back();
  stk.pop_back();

  auto S = stk.back();
  stk.pop_back();

  auto x = stk.back();
  stk.pop_back();

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == x)
    throw std::runtime_error("fn2c: got nullptr for x");
  if (nullptr == w)
    throw std::runtime_error("fn2c: got nullptr for w");
  if (nullptr == S)
    throw std::runtime_error("fn2c: got nullptr for S");
#endif

  auto v = S->call(2, {S, x, w});

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == v)
    throw std::runtime_error("fn2c: F returned nullptr");
#endif

  stk.push_back(v);
}

}
