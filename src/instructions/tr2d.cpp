#include "instr_helpers.hpp"
namespace cxbqn::vm::instructions {

void tr2d(std::vector<O<Value>> &stk) {
  auto f = stk.back();
  stk.pop_back();

  auto g = stk.back();
  stk.pop_back();

  CXBQN_DEBUG("tr2d:f={},g={}", CXBQN_STR_NC(f), CXBQN_STR_NC(g));

  stk.push_back(make_shared<Atop>(f, g));
}

}
