#include "instr_helpers.hpp"
namespace cxbqn::vm::instructions {

void alim(const ByteCodeRef bc, uz &pc, std::vector<O<Value>> &stk,
          observer_ptr<CompUnit> cu) {
  const auto i = bc[++pc];
  auto refer = dyncast<Reference>(stk.back());
  auto it = std::find_if(cu->_exported.begin(), cu->_exported.end(),
                         [i](auto e) { return e.second == i; });
  refer->tag = (*it).first;
}

} // namespace cxbqn::vm::instructions
