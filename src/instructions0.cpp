#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <deque>
#include <sstream>

namespace cxbqn::vm::instructions {

using namespace cxbqn::types;

namespace {

template <bool ShouldVarBeSet> void set(std::deque<Value *> stk, Scope *scp) {
  CXBQN_DEBUG("setn:enter");

  // Reference this instruction is assigning to
  auto *opaque_refer = stk.back();
  stk.pop_back();

  // Value the reference will be assigned to
  auto *value = stk.back();
  stk.pop_back();

  CXBQN_DEBUG("setn:ref={},val={}", CXBQN_STR_NC(opaque_refer), CXBQN_STR_NC(value));

#ifdef CXBQN_DEEPCHECKS
  if (not opaque_refer->t()[t_Reference]) {
    CXBQN_CRIT("setn: trying to set reference without t_Reference bit set.");
    CXBQN_CRIT("raw bits={}, val={}", opaque_refer->t(), *opaque_refer);
  }
#endif

  // If we're setting a reference, the type is either reference or refarray.
  // If the masked type matches t_Array, we know we're working with an array.
  if (opaque_refer->t()[t_RefArray]) {
    auto *aref = dynamic_cast<RefArray *>(opaque_refer);
    auto *aval = dynamic_cast<Array*>(value);
#ifdef CXBQN_DEEPCHECKS
    if (nullptr == aref)
      throw std::runtime_error(
          "setn: Could not cast reference to type RefArray");
    if (nullptr == aval)
      throw std::runtime_error(
          "setn: Could not cast value to type Array when assigning to RefArray");
#endif
    for (int i=0; i < aval->N; i++)
      scp->set(ShouldVarBeSet, aref->getref(i), aval->values[i]);
    stk.push_back(aval);
  } else {
    auto *refer = dynamic_cast<Reference *>(opaque_refer);
#ifdef CXBQN_DEEPCHECKS
    if (nullptr == refer)
      throw std::runtime_error(
          "setn: Could not cast reference to type Reference");
#endif
    scp->set(ShouldVarBeSet, refer, value);
    stk.push_back(refer);
  }
}

} // namespace

void setu(std::deque<Value *> &stk, Scope *scp) { set<true>(stk, scp); }

void setn(std::deque<Value *> &stk, Scope *scp) { set<false>(stk, scp); }

void varm(const ByteCodeRef bc, uz &pc, std::deque<Value *> &stk) {
  const auto depth = bc[++pc];
  const auto pos_in_parent = bc[++pc];
  stk.push_back(new types::Reference(static_cast<uz>(depth),
                                     static_cast<uz>(pos_in_parent)));
}

void varo(const ByteCodeRef bc, uz &pc, std::deque<Value *> &stk, Scope *scp) {
  const auto n_frames_up = bc[++pc];
  const auto local_variable_idx = bc[++pc];
  scp = scp->get_nth_parent(n_frames_up);
  CXBQN_DEBUG("varo:scope={},localidx={},framesup={}", *scp,
              local_variable_idx, n_frames_up);
  CXBQN_DEBUG_NC("varo:pushing var={}", scp->vars[local_variable_idx]);
  stk.push_back(scp->vars[local_variable_idx]);
}

void fn10(const ByteCodeRef bc, uz &pc, std::deque<Value *> &stk) {
  auto *S = stk.back();
  stk.pop_back();

  auto *x = stk.back();
  stk.pop_back();

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == x)
    throw std::runtime_error("fn10: got nullptr for x");
  if (nullptr == S)
    throw std::runtime_error("fn10: got nullptr for S");
#endif

  CXBQN_DEBUG("fn10:calling S={} on x={}", CXBQN_STR_NC(S), CXBQN_STR_NC(x));
  auto *v = S->call(1, {S, x});
  CXBQN_DEBUG("fn10:returning {}", CXBQN_STR_NC(v));
#ifdef CXBQN_DEEPCHECKS
  if (nullptr == v)
    throw std::runtime_error("fn10: S returned nullptr");
#endif

  stk.push_back(v);
}

void fn20(const ByteCodeRef bc, uz &pc, std::deque<Value *> &stk) {
  auto *w = stk.back();
  stk.pop_back();

  auto *S = stk.back();
  stk.pop_back();

  auto *x = stk.back();
  stk.pop_back();

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == x)
    throw std::runtime_error("FN20: got nullptr for x");
  if (nullptr == w)
    throw std::runtime_error("FN20: got nullptr for w");
  if (nullptr == S)
    throw std::runtime_error("FN20: got nullptr for S");
#endif

  auto *v = S->call(2, {S, x, w});

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == v)
    throw std::runtime_error("FN20: F returned nullptr");
#endif

  stk.push_back(v);
}

void dfnd(const ByteCodeRef bc, uz &pc, std::deque<Value *> &stk, Scope *scp) {
  auto blk_idx = bc[++pc];

  const auto blk = scp->blks[blk_idx];
  CXBQN_DEBUG("dfnd:pc={},block={}", pc, blk);

  if (blk.def.type == BlockType::func && blk.def.immediate) {
    auto *child = new Scope(scp, scp->blks, blk_idx);
    const auto blk = scp->blks[blk_idx];
    auto [bc, nvars] = blk.body();
    std::deque<Value *> stk_;

    CXBQN_DEBUG("dfnd:recursing into vm");
    auto *ret = vm::vm(bc, child->consts, stk_, child);
    stk.push_back(ret);
  } else {
    auto *F = new BlockInst(scp, blk_idx);
    stk.push_back(F);
  }
}

} // namespace cxbqn::vm::instructions
