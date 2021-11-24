#include "instr_helpers.hpp"
namespace cxbqn::vm::instructions {

void fldo(const ByteCodeRef bc, uz &pc, std::vector<O<Value>> &stk,
          O<CompUnit> cu) {
  fmt::print("fldo\n");
  auto i = bc[++pc];

  auto ns = dynamic_pointer_cast<Namespace>(stk.back());
  stk.pop_back();

  auto it = std::find_if(cu->_exported.begin(), cu->_exported.end(),
                         [i](auto e) { return e.second == i; });
  if (it == cu->_exported.end())
    throw std::runtime_error("fldo:could not find exported var");

  auto ret = ns->get((*it).first);
  stk.push_back(ret);
}

} // namespace cxbqn::vm::instructions
