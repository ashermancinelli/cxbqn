#include <cxbqn/cxbqn.hpp>
#include <deque>
#include <cxbqn/debug.hpp>
#include <sstream>

namespace cxbqn::vm::instructions {

using namespace cxbqn::types;

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

  scp->set(refer, value);

  stk.push_back(refer);
}

} // namespace cxbqn::vm::instructions
