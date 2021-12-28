#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Deshape::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("⥊: nargs={},args={}", nargs, args);
  XNULLCHK("⥊");

  const bool iswarr = t_Array == type_builtin(args[2]);
  const bool isxarr = t_Array == type_builtin(args[1]);
  auto xarr = isxarr ? dyncast<Array>(args[1]) : nullptr;

  if (1 == nargs) {
    if (isxarr) {
      auto ret = xarr->copy();
      ret->shape().clear();
      ret->shape().push_back(ret->N());
      return ret;
    } else {
      auto r = CXBQN_NEW(Array, 1);
      r->values[0] = args[1];
      return r;
    }
  }

  auto ret = CXBQN_NEW(Array);
  if (iswarr) {
    auto warr = dyncast<Array>(args[2]);
    for (int i = 0; i < warr->N(); i++)
      ret->shape().push_back(
          static_cast<uz>(dyncast<Number>(warr->values[i])->v));
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
      ret->values[i] = args[1];
  else
    for (int i = 0; i < cnt; i++)
      ret->values[i] =
          xarr->values[i %
                       xarr->N()]; // values wrap when 𝕩 has insufficient length
  return ret;
}
} // namespace cxbqn::provides
