#include "instr_helpers.hpp"
namespace cxbqn::vm::instructions {

void tr3o(std::vector<O<Value>> &stk) {
  auto f = stk.back();
  stk.pop_back();

  auto g = stk.back();
  stk.pop_back();

  auto h = stk.back();
  stk.pop_back();

  CXBQN_DEBUG("tr3o:f={},g={},h={}", CXBQN_STR_NC(f), CXBQN_STR_NC(g),
              CXBQN_STR_NC(h));

  if (f->t()[t_Nothing]) {
    CXBQN_DEBUG("tr3o: pushing atop, f was nothing");
    stk.push_back(CXBQN_NEW(Atop, g, h));
  } else {
    CXBQN_DEBUG("tr3o: pushing fork, h was not nothing");
    stk.push_back(CXBQN_NEW(Fork, f, g, h));
  }
}

} // namespace cxbqn::vm::instructions
