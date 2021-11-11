#include <cxbqn/cxbqn.hpp>
#include <cxbqn/debug.hpp>
#include <deque>
#include <sstream>

namespace cxbqn::vm::instructions {

using namespace cxbqn::types;

namespace {

// We know we need to assign to a reference-type, but we don't know whether
// we're working with a reference or a reference array. This function checks
// that the types allign, eg a refer is being set to a value and a refarray is
// being set to an array.
template <bool ShouldVarBeSet>
static O<Value> safe_set_refer(O<Value> opaque_refer, O<Value> value,
                               Scope *scp) {

#ifdef CXBQN_DEEPCHECKS
  if (not opaque_refer->t()[t_Reference]) {
    CXBQN_CRIT("set_: trying to set reference without t_Reference bit set.");
    CXBQN_CRIT("raw bits={}, val={}", opaque_refer->t(), *opaque_refer);
  }
#endif

  // If we're setting a reference, the type is either reference or refarray.
  // If the masked type matches t_Array, we know we're working with an array.
  if (opaque_refer->t()[t_RefArray]) {
    auto aref = dynamic_pointer_cast<RefArray>(opaque_refer);
    auto aval = dynamic_pointer_cast<Array>(value);
#ifdef CXBQN_DEEPCHECKS
    if (nullptr == aref)
      throw std::runtime_error(
          "setn: Could not cast reference to type RefArray");
    if (nullptr == aval)
      throw std::runtime_error("setn: Could not cast value to type Array when "
                               "assigning to RefArray");
#endif
    for (int i = 0; i < aval->N(); i++)
      scp->set(ShouldVarBeSet, aref->getref(i), aval->values[i]);
    return aval;

  } else {

    auto refer = dynamic_pointer_cast<Reference>(opaque_refer);
#ifdef CXBQN_DEEPCHECKS
    if (nullptr == refer)
      throw std::runtime_error(
          "setn: Could not cast reference to type Reference");
#endif
    scp->set(ShouldVarBeSet, refer, value);
    return value;
  }
}

template <bool ShouldVarBeSet>
static O<Value> set_un_helper(std::deque<O<Value>> &stk, Scope *scp) {
  // Reference this instruction is assigning to
  auto opaque_refer = stk.back();
  stk.pop_back();

  // Value the reference will be assigned to
  auto value = stk.back();
  stk.pop_back();

  CXBQN_DEBUG("set_un_helper:ref={},val={}", CXBQN_STR_NC(opaque_refer),
              CXBQN_STR_NC(value));

  return safe_set_refer<ShouldVarBeSet>(opaque_refer, value, scp);
}

static O<Value> setm_ref(O<Value> F, O<Value> x, O<Value> r, Scope *scp) {
  auto refer = dynamic_pointer_cast<Reference>(r);
  auto v = F->call(2, {F, x, scp->get(refer)});

  // Set the new value of the reference, and push it back on the stack
  scp->set(true, refer, v);
  return v;
}

static O<Value> setm_refarray(O<Value> F, O<Value> x, O<Value> r, Scope *scp) {
  auto refarr = dynamic_pointer_cast<RefArray>(r);
  auto varr = make_shared<Array>(refarr->N());

  // create an array from the reference array to pass into F
  for (int i = 0; i < refarr->N(); i++)
    varr->values.push_back(scp->get(refarr->getref(i)));

  auto v = F->call(2, {F, x, varr});

  safe_set_refer<true>(r, v, scp);

  return r;
}

} // namespace

void setu(std::deque<O<Value>> &stk, Scope *scp) {
  stk.push_back(set_un_helper<true>(stk, scp));
}

void setn(std::deque<O<Value>> &stk, Scope *scp) {
  stk.push_back(set_un_helper<false>(stk, scp));
}

void setm(std::deque<O<Value>> &stk, Scope *scp) {
  auto r = stk.back();
  stk.pop_back();

  auto F = stk.back();
  stk.pop_back();

  auto x = stk.back();
  stk.pop_back();

  CXBQN_DEBUG("setm:x={},F={},r={}", CXBQN_STR_NC(x), CXBQN_STR_NC(F),
              CXBQN_STR_NC(r));

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == r)
    throw std::runtime_error("setm: got nullptr for r");
  if (nullptr == F)
    throw std::runtime_error("setm: got nullptr for R");
  if (nullptr == x)
    throw std::runtime_error("setm: got nullptr for x");
#endif

  // F is called with 𝕩 and dereferenced r

  // Are we working with an array of references?
  if (r->t()[t_RefArray]) {
    stk.push_back(setm_refarray(F, x, r, scp));
  }
  // Or just a reference?
  else {
    stk.push_back(setm_ref(F, x, r, scp));
  }
}

void setc(std::deque<O<Value>> &stk, Scope *scp) {
  auto r = stk.back();
  stk.pop_back();

  auto F = stk.back();
  stk.pop_back();

  CXBQN_DEBUG("setm:F={},r={}", CXBQN_STR_NC(F), CXBQN_STR_NC(r));

  // F is called with 𝕩 and dereferenced r
  auto refer = dynamic_pointer_cast<Reference>(r);
  auto v = F->call(2, {F, scp->get(refer), bi_Nothing()});

  // Set the new value of the reference, and push it back on the stack
  scp->set(true, refer, v);

  stk.push_back(v);
}

void varm(const ByteCodeRef bc, uz &pc, std::deque<O<Value>> &stk) {
  const auto depth = bc[++pc];
  const auto pos_in_parent = bc[++pc];
  stk.push_back(make_shared<Reference>(static_cast<uz>(depth),
                                     static_cast<uz>(pos_in_parent)));
}

void varo(const ByteCodeRef bc, uz &pc, std::deque<O<Value>> &stk, Scope *scp) {
  const auto n_frames_up = bc[++pc];
  const auto local_variable_idx = bc[++pc];
  scp = scp->get_nth_parent(n_frames_up);
  CXBQN_DEBUG("varo:scope={},localidx={},framesup={}", *scp, local_variable_idx,
              n_frames_up);
  CXBQN_DEBUG_NC("varo:pushing var={}", scp->vars[local_variable_idx]);
  stk.push_back(scp->vars[local_variable_idx]);
}

void fn1c(std::deque<O<Value>> &stk) {
  auto S = stk.back();
  stk.pop_back();

  auto x = stk.back();
  stk.pop_back();

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == x)
    throw std::runtime_error("fn1c: got nullptr for x");
  if (nullptr == S)
    throw std::runtime_error("fn1c: got nullptr for S");
#endif

  CXBQN_DEBUG("fn1c:calling S={} on x={}", CXBQN_STR_NC(S), CXBQN_STR_NC(x));
  auto v = S->call(1, {S, x, bi_Nothing()});
  CXBQN_DEBUG("fn1c:returning {}", CXBQN_STR_NC(v));
#ifdef CXBQN_DEEPCHECKS
  if (nullptr == v)
    throw std::runtime_error("fn1c: S returned nullptr");
#endif

  stk.push_back(std::move(v));
}

void fn1o(std::deque<O<Value>> &stk) {
  auto S = stk.back();
  stk.pop_back();

  auto x = stk.back();
  stk.pop_back();

  if (x->t()[t_Nothing]) {
    stk.push_back(bi_Nothing());
    return;
  }

  stk.push_back(S->call(1, {S, x, bi_Nothing()}));
}

void fn2c(std::deque<O<Value>> &stk) {
  auto w = stk.back();
  stk.pop_back();

  auto S = stk.back();
  stk.pop_back();

  auto x = stk.back();
  stk.pop_back();

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == x)
    throw std::runtime_error("fn2c: got nullptr for x");
  if (nullptr == w)
    throw std::runtime_error("fn2c: got nullptr for w");
  if (nullptr == S)
    throw std::runtime_error("fn2c: got nullptr for S");
#endif

  auto v = S->call(2, {S, x, w});

#ifdef CXBQN_DEEPCHECKS
  if (nullptr == v)
    throw std::runtime_error("fn2c: F returned nullptr");
#endif

  stk.push_back(v);
}

void fn2o(std::deque<O<Value>> &stk) {
  auto w = stk.back();
  stk.pop_back();

  auto S = stk.back();
  stk.pop_back();

  auto x = stk.back();
  stk.pop_back();

  if (w->t()[t_Nothing]) {
    if (x->t()[t_Nothing]) {
      CXBQN_DEBUG("fn2o: got nothing for 𝕩 and 𝕨, just pushing nothing");
      stk.push_back(bi_Nothing());
      return;
    }

    CXBQN_DEBUG("fn2o: got nothing for 𝕩 and 𝕨, just pushing nothing");
    stk.push_back(S->call(1, {S, x, bi_Nothing()}));
    return;
  }

  CXBQN_DEBUG("fn2o: got vals for both 𝕩 and 𝕨, calling dyadically");
  auto v = S->call(2, {S, x, w});
  stk.push_back(v);
}

void dfnd(const ByteCodeRef bc, uz &pc, std::deque<O<Value>> &stk, Scope *scp) {
  auto blk_idx = bc[++pc];

  const auto blk = scp->blks[blk_idx];
  CXBQN_DEBUG("dfnd:pc={},block={}", pc, blk);

  if (blk.def.type == BlockType::func && blk.def.immediate) {
    auto *child = new Scope(scp, scp->blks, blk_idx);
    const auto blk = scp->blks[blk_idx];
    auto [bc, nvars] = blk.body();
    std::deque<O<Value>> stk_;

    CXBQN_DEBUG("dfnd:recursing into vm");
    auto ret = vm::vm(bc, child->consts, stk_, child);
    stk.push_back(ret);
  } else {
    stk.push_back(make_shared<BlockInst>(scp, blk_idx));
  }
}

void arro(const ByteCodeRef bc, uz &pc, std::deque<O<Value>> &stk) {
  const auto list_len = bc[++pc];
  auto ar = make_shared<Array>(list_len, stk);
  stk.push_back(ar);
}

void arrm(const ByteCodeRef bc, uz &pc, std::deque<O<Value>> &stk) {
  const auto list_len = bc[++pc];
  auto ar = make_shared<RefArray>(list_len, stk);
  stk.push_back(ar);
}

void md1c(std::deque<O<Value>> &stk) {
  auto f = stk.back();
  stk.pop_back();

  auto opaque_r = stk.back();
  stk.pop_back();

  CXBQN_DEBUG("md1c:r={},f={}", CXBQN_STR_NC(opaque_r), CXBQN_STR_NC(f));

  auto r = dynamic_pointer_cast<BlockInst>(opaque_r);
  if (nullptr != r and r->imm()) {
    auto v = r->call(1, {opaque_r, f});
    stk.push_back(v);
  } else {
    stk.push_back(make_shared<Md1Deferred>(f, opaque_r));
  }
}

void md2c(std::deque<O<Value>> &stk) {
  auto f = stk.back();
  stk.pop_back();

  auto opaque_r = stk.back();
  stk.pop_back();

  auto g = stk.back();
  stk.pop_back();

  CXBQN_DEBUG("md1c:(F _r_ G)=({} {} {})", CXBQN_STR_NC(f),
              CXBQN_STR_NC(opaque_r), CXBQN_STR_NC(g));

  auto r = dynamic_pointer_cast<BlockInst>(opaque_r);

  if (nullptr != r and r->imm()) {
    auto v = r->call(2, {opaque_r, f, g});
    stk.push_back(v);
  } else {
    stk.push_back(make_shared<Md2Deferred>(f, opaque_r, g));
  }
}

void tr2d(std::deque<O<Value>> &stk) {
  auto f = stk.back();
  stk.pop_back();

  auto g = stk.back();
  stk.pop_back();

  CXBQN_DEBUG("tr2d:f={},g={}", CXBQN_STR_NC(f), CXBQN_STR_NC(g));

  stk.push_back(make_shared<Atop>(f, g));
}

// fork: ⟨…,h,g,f⟩ → (f g h)
void tr3d(std::deque<O<Value>> &stk) {
  auto f = stk.back();
  stk.pop_back();

  auto g = stk.back();
  stk.pop_back();

  auto h = stk.back();
  stk.pop_back();

  CXBQN_DEBUG("tr3d:f={},g={},h={}", CXBQN_STR_NC(f), CXBQN_STR_NC(g),
              CXBQN_STR_NC(h));

  stk.push_back(make_shared<Fork>(f, g, h));
}

void tr3o(std::deque<O<Value>> &stk) {
  auto f = stk.back();
  stk.pop_back();

  auto g = stk.back();
  stk.pop_back();

  auto h = stk.back();
  stk.pop_back();

  CXBQN_DEBUG("tr3d:f={},g={},h={}", CXBQN_STR_NC(f), CXBQN_STR_NC(g),
              CXBQN_STR_NC(h));

  if (h->t()[t_Nothing]) {
    CXBQN_DEBUG("tr3o: pushing atop, h was nothing");
    stk.push_back(make_shared<Atop>(f, g));
  } else {
    CXBQN_DEBUG("tr3o: pushing fork, h was not nothing");
    stk.push_back(make_shared<Fork>(f, g, h));
  }
}

} // namespace cxbqn::vm::instructions
