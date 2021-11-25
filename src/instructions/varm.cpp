#include "instr_helpers.hpp"
namespace cxbqn::vm::instructions {

void varm(const ByteCodeRef bc, uz &pc, std::vector<O<Value>> &stk) {
  const auto depth = bc[++pc];
  const auto pos_in_parent = bc[++pc];
  stk.push_back(CXBQN_NEW(Reference,static_cast<uz>(depth), static_cast<uz>(pos_in_parent)));
}

}
