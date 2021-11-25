#include "instr_helpers.hpp"
namespace cxbqn::vm::instructions {
namespace {

// We know we need to assign to a reference-type, but we don't know whether
// we're working with a reference or a reference array. This function checks
// that the types allign, eg a refer is being set to a value and a refarray is
// being set to an array.
template <bool ShouldVarBeSet>
static O<Value> safe_set_refer(O<Value> opaque_refer, O<Value> value,
                               shared_ptr<Scope> scp) {

#ifdef CXBQN_DEEPCHECKS
  if (not opaque_refer->t()[t_Reference]) {
    CXBQN_CRIT("set_: trying to set reference without t_Reference bit set.");
    CXBQN_CRIT("raw bits={}, val={}", opaque_refer->t(), *opaque_refer);
  }
#endif

  // If we're setting a reference, the type is either reference or refarray.
  // If the masked type matches t_Array, we know we're working with an array.
  if (opaque_refer->t()[t_RefArray]) {
    auto aref = dyncast<RefArray>(opaque_refer);
#ifdef CXBQN_DEEPCHECKS
    if (nullptr == aref)
      throw std::runtime_error(
          "setn: Could not cast reference to type RefArray");
#endif

    if (t_Namespace == type_builtin(value)) {
      for (int i = 0; i < aref->N(); i++) {
        auto r = aref->getref(i);
        auto tmp_scp = scp->get_nth_parent(r->depth);
        r->tag = tmp_scp->names[r->position_in_parent];
        scp->set(ShouldVarBeSet, aref->getref(i), value);
      }
      return value;
    } else if (value->t()[t_DataValue]) {
      for (int i = 0; i < aref->N(); i++)
        scp->set(ShouldVarBeSet, aref->getref(i), value);
      return value;
    } else {

      auto aval = dyncast<Array>(value);
#ifdef CXBQN_DEEPCHECKS
      if (nullptr == aval)
        throw std::runtime_error("setn: Could not cast value to type Array when "
                                 "assigning to RefArray");
#endif
      for (int i = 0; i < aval->N(); i++)
        scp->set(ShouldVarBeSet, aref->getref(i), aval->values[i]);
      return aval;
    }
  } else {

    auto refer = dyncast<Reference>(opaque_refer);
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
static O<Value> set_un_helper(std::vector<O<Value>> &stk, shared_ptr<Scope> scp) {
  // Reference this instruction is assigning to
  auto opaque_refer = stk.back();
  stk.pop_back();

  // Value the reference will be assigned to
  auto value = stk.back();
  stk.pop_back();

  CXBQN_DEBUG("set_un_helper:ref={},val={}", CXBQN_STR_NC(opaque_refer),
              CXBQN_STR_NC(value));
  // fmt::print("set_un_helper:ref={},val={}\n", CXBQN_STR_NC(opaque_refer),
              // CXBQN_STR_NC(value));

  return safe_set_refer<ShouldVarBeSet>(opaque_refer, value, scp);
}

static O<Value> setm_ref(O<Value> F, O<Value> x, O<Value> r, shared_ptr<Scope> scp) {
  auto refer = dyncast<Reference>(r);
  auto v = F->call(2, {F, x, scp->get(refer)});

  // Set the new value of the reference, and push it back on the stack
  scp->set(true, refer, v);
  return v;
}

static O<Value> setm_refarray(O<Value> F, O<Value> x, O<Value> r,
                              shared_ptr<Scope> scp) {
  auto refarr = dyncast<RefArray>(r);
  auto varr = make_shared<Array>(refarr->N());

  // create an array from the reference array to pass into F
  for (int i = 0; i < refarr->N(); i++)
    varr->values.push_back(scp->get(refarr->getref(i)));

  auto v = F->call(2, {F, x, varr});

  safe_set_refer<true>(r, v, scp);

  return r;
}

} // namespace

void setu(std::vector<O<Value>> &stk, shared_ptr<Scope> scp) {
  stk.push_back(set_un_helper<true>(stk, scp));
}

void setn(std::vector<O<Value>> &stk, shared_ptr<Scope> scp) {
  stk.push_back(set_un_helper<false>(stk, scp));
}

void setm(std::vector<O<Value>> &stk, shared_ptr<Scope> scp) {
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

void setc(std::vector<O<Value>> &stk, shared_ptr<Scope> scp) {
  auto r = stk.back();
  stk.pop_back();

  auto F = stk.back();
  stk.pop_back();

  CXBQN_DEBUG("setm:F={},r={}", CXBQN_STR_NC(F), CXBQN_STR_NC(r));

  // F is called with 𝕩 and dereferenced r
  auto refer = dyncast<Reference>(r);
  auto v = F->call(1, {F, scp->get(refer), bi_Nothing()});

  // Set the new value of the reference, and push it back on the stack
  scp->set(true, refer, v);

  stk.push_back(v);
}
} // namespace cxbqn::vm::instructions
