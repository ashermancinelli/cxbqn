#include "instr_helpers.hpp"
namespace cxbqn::vm::instructions {

void arro(const ByteCodeRef bc, uz &pc, std::vector<O<Value>> &stk) {
  const auto list_len = bc[++pc];
  auto ar = make_shared<Array>(list_len, stk);
  stk.push_back(ar);
}

}
