#include "provides_helpers.hpp"

namespace cxbqn::provides {

bool eq_recursive(O<Value> ox, O<Value> ow) {
  /*
   * If the builtin types differ, that's an easy case to rule out. We can also
   * assume from this point out that the bultin type of x and w will be the
   * same.
   */
  const auto tbx = type_builtin(ox), tbw = type_builtin(ow);
  if ((t_Number == tbx or t_Character == tbx) and
      (t_Number == tbw or t_Character == tbw))
    return feq_helper(dyncast<Number>(ox)->v,
                      dyncast<Number>(ow)->v);

  if (type_builtin(ox) != type_builtin(ow))
    return false;

  /* Use pointer comparison for blockinst's */
  if (auto xf = dyncast<BlockInst>(ox)) {
    auto wf = dyncast<BlockInst>(ow);
    if (!wf) return false;
    return xf == wf;
  }
  if (auto x = dyncast<Md1Deferred>(ox)) { // both must be deferred
    auto w = dyncast<Md1Deferred>(ow);
    if (!w) return false;
    return eq_recursive(x->f, w->f) and eq_recursive(x->m1, w->m1);
  }
  if (auto x = dyncast<Md2Deferred>(ox)) { // both must be deferred
    auto w = dyncast<Md2Deferred>(ow);
    if (!w) return false;
    return eq_recursive(x->f, w->f) and eq_recursive(x->m2, w->m2) and
           eq_recursive(x->g, w->g);
  }

  if (t_Md1 == type_builtin(ox)) {
    if (ox->t()[t_Deferred] != ow->t()[t_Deferred])
      return false;
    // if not deferred, just pointer comparison
    return ox == ow;
  }

  if (t_Md2 == type_builtin(ox)) {
    if (ox->t()[t_Deferred] != ow->t()[t_Deferred])
      return false;
    // if not deferred, just pointer comparison
    return ox == ow;
  }

  /* Compare fields for derived types */
  if (auto x = dyncast<Fork>(ox)) {
    auto w = dyncast<Fork>(ow);
    if (!w) return false;
    return eq_recursive(x->f, w->f) and eq_recursive(x->g, w->g) and
           eq_recursive(x->h, w->h);
  }
  if (auto x = dyncast<Atop>(ox)) {
    auto w = dyncast<Atop>(ow);
    if (!w) return false;
    return eq_recursive(x->f, w->f) and eq_recursive(x->g, w->g);
  }

  return ox == ow;
}

#define CHR_MAX 1114111
O<Value> check_char(O<Value> v) {
  if (t_Character != type_builtin(v))
    throw std::runtime_error("internal: invalid value passed to check_char");
  auto f = dyncast<Character>(v)->v;
  if (f < 0 || f > CHR_MAX)
    throw std::runtime_error("invalid code point");
  return v;
}

// Recursively find the max depth of each element, and max reduce
uz array_depth_helper(uz init, O<Value> v) {
  CXBQN_DEBUG("array_depth_helper:init={},value={}", init, CXBQN_STR_NC(v));
  if (t_Array == type_builtin(v)) {
    auto ar = dyncast<Array>(v);
    return init +
           std::accumulate(ar->values.begin(), ar->values.end(), 1,
                           [](uz acc, auto b) {
                             return std::max(acc, array_depth_helper(0, b));
                           });
  } else
    return 1 + init;
}

bool equivilant_helper(O<Value> a, O<Value> b) {
  if (a->t()[t_DataValue] and b->t()[t_DataValue])
    return feq_helper(dyncast<Number>(a)->v,
                      dyncast<Number>(b)->v);
  else if (t_Array == type_builtin(a) and t_Array == type_builtin(b)) {
    auto av = dyncast<Array>(a);
    auto bv = dyncast<Array>(b);
    if (av->N() != bv->N())
      return false;
    for (int i = 0; i < av->N(); i++)
      if (!equivilant_helper(av->values[i], bv->values[i]))
        return false;
  }
  throw std::runtime_error("equivilant_helper: something went wrong");
}

}
