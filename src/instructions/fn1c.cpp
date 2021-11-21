#include "instr_helpers.hpp"
namespace cxbqn::vm::instructions {

void fn1c(std::vector<O<Value>> &stk) {
  auto S = stk.back();
  stk.pop_back();

  auto x = stk.back();
  stk.pop_back();

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == x)
    throw std::runtime_error("fn1c: got nullptr for x");
  if (nullptr == S)
    throw std::runtime_error("fn1c: got nullptr for S");
#endif

  CXBQN_DEBUG("fn1c:calling S={} on x={}", CXBQN_STR_NC(S), CXBQN_STR_NC(x));
  auto v = S->call(1, {S, x, bi_Nothing()});
  CXBQN_DEBUG("fn1c:returning {}", CXBQN_STR_NC(v));
#ifdef CXBQN_DEEPCHECKS
  if (nullptr == v)
    throw std::runtime_error("fn1c: S returned nullptr");
#endif

  stk.push_back(v);
}

}
