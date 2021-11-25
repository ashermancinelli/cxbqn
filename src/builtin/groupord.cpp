#include "provides_helpers.hpp"

namespace cxbqn::provides {

#define SYMBOL "GroupOrd"
O<Value> GroupOrd::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG(SYMBOL ": nargs={},args={}", nargs, args);
  XNULLCHK(SYMBOL);
  auto w = dyncast<Array>(args[2]);
  auto x = dyncast<Array>(args[1]);

  if (0 == w->N())
    return make_shared<Array>(0);

  std::vector<uz> tmp(w->N(), 0);
  CXBQN_DEBUG("wn={},xn={},tmpn={}", w->N(), x->N(), tmp.size());
  for (int i = 1; i < w->N(); i++) {
    tmp[i] = tmp[i - 1] + static_cast<uz>(dyncast<Number>(w->values[i - 1])->v);
    CXBQN_DEBUG("tmp[{}]={} w[i]={}", i, tmp[i],
                CXBQN_STR_NC(w->values[i - 1]));
  }

  const auto retlen = tmp.back() + static_cast<uz>(dyncast<Number>(w->values.back())->v);
  CXBQN_DEBUG("return len={}", retlen);

  std::vector<f64> retv(retlen, 0);
  for (int i = 0; i < x->N(); i++) {
    const auto e = dyncast<Number>(x->values[i])->v;
    if (fge_helper(e, 0.0)) {
      const auto idx = static_cast<uz>(e);
      retv[tmp[idx]++] = static_cast<f64>(i);
    }
  }

  auto ret = make_shared<Array>(retlen);
  for (int i = 0; i < retlen; i++) {
    ret->values[i] = make_shared<Number>(retv[i]);
  }
  return ret;
}
#undef SYMBOL
}
