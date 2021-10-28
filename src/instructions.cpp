#include <cxbqn.hpp>
#include <deque>
#include <cxbqn_debug.hpp>
#include <sstream>

namespace cxbqn::vm::instructions {

using namespace cxbqn::types;

void assign(Reference *r, Value *v, Scope *scp) {
  // Number of scopes to ascend
  auto n = r->depth;
  CXBQN_DEBUG("cxbqn::vm::instructions::assign:n={}", n);

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == r)
    throw std::runtime_error("assign: got nullptr reference");
  if (nullptr == v)
    throw std::runtime_error("assign: got nullptr value");
  if (nullptr == scp)
    throw std::runtime_error("assign: got nullptr scope");
#endif

  // Walk the scope descendence to find the target scope
  while (n--) {
    scp = scp->parent;
#ifdef CXBQN_DEEPCHECKS
    if (nullptr == scp)
      throw std::runtime_error(
          "assign: got nullptr scope when walking the scope tree");
#endif
  }

  CXBQN_DEBUG("cxbqn::vm::instructions::assign:r->pos={}", r->position_in_parent);
#ifdef CXBQN_DEEPCHECKS
  if (r->position_in_parent >= scp->vars.size())
    throw std::runtime_error(
        "Attempted to assign value to reference in location outside of bounds "
        "in the intended scope");
#endif

  // assign to the underlying value
  scp->vars[r->position_in_parent] = v;
}

void setn(std::deque<Value *> stk, Scope *scp) {

  CXBQN_DEBUG("SETN:enter");
  debug::vdbg("setn:stack", stk);
  // Reference this instruction is assigning to
  auto *opaque_refer = stk.back();
  stk.pop_back();

  // Value the reference will be assigned to
  auto *value = stk.back();
  stk.pop_back();

  auto *refer = dynamic_cast<Reference *>(opaque_refer);
#ifdef CXBQN_DEEPCHECKS
  if (nullptr == refer)
    throw std::runtime_error(
        "SETN: Could not cast reference to type Reference");
#endif

  assign(refer, value, scp);

  stk.push_back(refer);
}

} // namespace cxbqn::vm::instructions
