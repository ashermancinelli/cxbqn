#include "instr_helpers.hpp"
namespace cxbqn::vm::instructions {

void fldo(const ByteCodeRef bc, uz &pc, std::vector<O<Value>> &stk,
          observer_ptr<CompUnit> cu) {
  auto i = bc[++pc];

  auto ns = dyncast<Namespace>(stk.back());
  stk.pop_back();

//  for (auto it = cu->_exported.begin(); it != cu->_exported.end(); it++)
//    fmt::print("k={}\n",(*it).first);

  auto it = std::find_if(cu->_exported.begin(), cu->_exported.end(),
                         [i](auto e) { return e.second == i; });

  if (it == cu->_exported.end())
    throw std::runtime_error("fldo: could not find exported var");

  stk.push_back(ns->get((*it).first));
}

} // namespace cxbqn::vm::instructions
