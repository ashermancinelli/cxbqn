#include "instr_helpers.hpp"
namespace cxbqn::vm::instructions {

void alim(const ByteCodeRef bc, uz &pc, std::vector<O<Value>> &stk,
          O<std::unordered_map<std::string, uz>> exported) {
  const auto i = bc[++pc];

  auto ns = stk.back();
  stk.pop_back();

  stk.push_back(O<Value>(new VarAlias(nullptr, std::string{""})));
}

} // namespace cxbqn::vm::instructions
