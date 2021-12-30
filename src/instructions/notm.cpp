#include "instr_helpers.hpp"
namespace cxbqn::vm::instructions {

void notm(std::vector<O<Value>> &stk) {
  auto nullr = CXBQN_NEW(Reference, 0, 0);
  nullr->extra_annot = annot(t_NullReference);
  stk.push_back(nullr);
}

} // namespace cxbqn::vm::instructions
