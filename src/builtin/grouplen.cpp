#include "provides_helpers.hpp"

namespace cxbqn::provides {

#define SYMBOL "GroupLen"
O<Value> GroupLen::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG(SYMBOL ": nargs={},args={}", nargs, args);
  XNULLCHK(SYMBOL);
  auto x = std::dynamic_pointer_cast<Array>(args[1]);
  auto w =
      std::dynamic_pointer_cast<Number>(args[2]); // only use if nargs == 2!
  const auto init = (2 == nargs ? w->v : 0) - 1;
  std::vector<f64> xs(x->N(), 0);
  for (int i = 0; i < x->N(); i++)
    xs[i] = dynamic_pointer_cast<Number>(x->values[i])->v;
  const auto l = std::accumulate(xs.begin(), xs.end(), init,
                                 [](auto a, auto b) { return std::max(a, b); });
  std::vector<f64> retv(static_cast<uz>(l + 1), 0);
  std::fill(retv.begin(), retv.end(), 0);
  for (auto e : xs)
    if (fge_helper(e, 0.0))
      retv[static_cast<uz>(e)]++;
  auto ret = make_shared<Array>(retv.size());
  for (int i = 0; i < ret->N(); i++)
    ret->values[i] = NN(retv[i]);
  return ret;
}
#undef SYMBOL
}