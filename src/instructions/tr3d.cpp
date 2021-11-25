#include "instr_helpers.hpp"
namespace cxbqn::vm::instructions {

// fork: ⟨…,h,g,f⟩ → (f g h)
void tr3d(std::vector<O<Value>> &stk) {
  auto f = stk.back();
  stk.pop_back();

  auto g = stk.back();
  stk.pop_back();

  auto h = stk.back();
  stk.pop_back();

  CXBQN_DEBUG("tr3d:f={},g={},h={}", CXBQN_STR_NC(f), CXBQN_STR_NC(g),
              CXBQN_STR_NC(h));

  stk.push_back(CXBQN_NEW(Fork,f, g, h));
}
}
