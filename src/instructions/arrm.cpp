#include "instr_helpers.hpp"
namespace cxbqn::vm::instructions {

void arrm(const ByteCodeRef bc, uz &pc, std::vector<O<Value>> &stk) {
  const auto list_len = bc[++pc];
  auto ar = make_shared<RefArray>(list_len, stk);
  stk.push_back(ar);
}

}
