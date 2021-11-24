#include "instr_helpers.hpp"
namespace cxbqn::vm::instructions {

void alim(const ByteCodeRef bc, uz &pc, std::vector<O<Value>> &stk,
          O<CompUnit> cu) {
  fmt::print("alim\n");
  const auto i = bc[++pc];
  auto refer = dynamic_pointer_cast<Reference>(stk.back());
  auto it = std::find_if(cu->_exported.begin(), cu->_exported.end(),
                         [i](auto e) { return e.second == i; });
  refer->tag = (*it).first;
  fmt::print("tag={}\n", refer->tag.value());
}

} // namespace cxbqn::vm::instructions
