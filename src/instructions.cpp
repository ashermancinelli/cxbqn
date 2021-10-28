#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <deque>
#include <sstream>

namespace cxbqn::vm::instructions {

using namespace cxbqn::types;

namespace {

template <bool ShouldVarBeSet> void set(std::deque<Value *> stk, Scope *scp) {

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

  scp->set(ShouldVarBeSet, refer, value);

  stk.push_back(refer);
}

} // namespace

void setu(std::deque<Value *> &stk, Scope *scp) { set<true>(stk, scp); }

void setn(std::deque<Value *> &stk, Scope *scp) { set<true>(stk, scp); }

void varm(std::vector<i32> &bc, uz &pc, std::deque<Value *> &stk) {
  const auto depth = bc[++pc];
  const auto pos_in_parent = bc[++pc];
  stk.push_back(new types::Reference(static_cast<uz>(depth),
                                     static_cast<uz>(pos_in_parent)));
}

void varo(std::vector<i32> &bc, uz &pc, std::deque<Value *> &stk, Scope* scp) {
  const auto local_variable_idx = bc[++pc];
  const auto n_frames_up = bc[++pc];
  scp = scp->get_nth_parent(n_frames_up);
  stk.push_back(scp->vars[local_variable_idx]);
}

void fn10(std::vector<i32> &bc, uz &pc, std::deque<Value *> &stk, Scope* scp) {
  auto *F = stk.back();
  stk.pop_back();

  auto *x = stk.back();
  stk.pop_back();

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == x)
    throw std::runtime_error("FN10: got nullptr for x");
  if (nullptr == x)
    throw std::runtime_error("FN10: got nullptr for F");
#endif

  auto *v = F->call(1, nullptr, x);
#ifdef CXBQN_DEEPCHECKS
  if (nullptr == v)
    throw std::runtime_error("FN10: F returned nullptr");
#endif

  stk.push_back(v);
}

} // namespace cxbqn::vm::instructions
