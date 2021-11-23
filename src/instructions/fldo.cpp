#include "instr_helpers.hpp"
namespace cxbqn::vm::instructions {

void fldo(const ByteCodeRef bc, uz& pc, std::vector<O<Value>> &stk) {
  auto i = bc[++pc];

  auto ns = dynamic_pointer_cast<Namespace>(stk.back());
  stk.push_back(ns->get(i));
}

}
