#include "provides_helpers.hpp"
#include <cxbqn/array_types.hpp>

namespace cxbqn::provides {

O<Value> Deshape::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("⥊: nargs={},args={}", nargs, args);
  XNULLCHK("⥊");

  auto x = args[1];
  auto w = args[2];
  const bool iswarr = t_Array == type_builtin(w);
  const bool isxarr = t_Array == type_builtin(x);
  auto xarr = isxarr ? dyncast<ArrayBase>(args[1]) : nullptr;

  if (1 == nargs) {
    if (isxarr) {
      auto ret = CXBQN_NEW(Array, xarr->N());
      for(int i=0;i<xarr->N();i++)
        ret->values[i]=xarr->get(i);
      return ret;
    } else {
      auto r = CXBQN_NEW(Array, 1);
      r->values[0] = args[1];
      return r;
    }
  }

  if (iswarr and isxarr and x->t()[t_TypedArray] and w->t()[t_TypedArray]) {
    throw std::runtime_error("foo");
  }

  // if either 𝕩 or 𝕨 is not a typed array, we'll have to fall back to hetero
  // arrays for the result
  auto ret = CXBQN_NEW(Array);

  if (iswarr) {
    auto warr = dyncast<ArrayBase>(args[2]);
    for (int i = 0; i < warr->N(); i++)
      ret->shape().push_back(
          static_cast<uz>(dyncast<Number>(warr->get(i))->v));
  } else {
    ret->shape().push_back(static_cast<uz>(dyncast<Number>(args[2])->v));
  }

  const auto cnt = std::accumulate(ret->shape().begin(), ret->shape().end(), 1,
                                   std::multiplies<uz>());
  if (0 == cnt)
    CXBQN_DEBUG("⥊: got count of 0, this is suspicious");

  ret->values.resize(cnt);

  if (!isxarr)
    for (int i = 0; i < cnt; i++)
      ret->values[i] = x;
  else
    for (int i = 0; i < cnt; i++)
      // values wrap when 𝕩 has insufficient length
      ret->values[i] = xarr->get(i % xarr->N());

  return ret;
}
} // namespace cxbqn::provides
