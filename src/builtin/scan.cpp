#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Scan::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("`: nargs={},args={}", nargs, args);
  XNULLCHK("`");
  if (t_Array != type_builtin(args[1]))
    throw std::runtime_error("`: 𝕩 must have rank at least 1");

  // if ((1 == nargs) != (args[2]->t()[t_Nothing])) throw std::runtime_error("`:
  // got · for 𝕨 with 2 args, or non-· with 1 arg");

  auto x = dyncast<Array>(args[1]);

  if (x->N() == 0) {
    if (1 == x->shape.size() and 0 == x->shape.back())
      return CXBQN_NEW(Array, 0);
    auto ret = CXBQN_NEW(Array, 0);
    ret->values.clear();
    ret->shape = x->shape;
  }

  auto w = args[2];
  auto F = args[4];

  auto sh = x->shape;
  auto iswarr = (t_Array == type_builtin(w));
  if (2 == nargs) {
    auto w_rank = iswarr ? dyncast<Array>(w)->shape.size() : 0;
    if (1 + w_rank != x->shape.size())
      throw std::runtime_error("`: rank of 𝕨 must be cell rank of 𝕩");
    if (iswarr) {
      const auto &wsh = dyncast<Array>(w)->shape;
      for (int i = 0; i < x->shape.size() - 1; i++)
        if (wsh[i] != x->shape[i + 1])
          throw std::runtime_error("`: shape of 𝕨 must be cell shape of 𝕩");
    }
  }

  auto ret = CXBQN_NEW(Array);
  ret->values.resize(x->N());
  ret->shape.resize(x->shape.size());
  std::copy(x->shape.begin(), x->shape.end(), ret->shape.begin());

  // product reduction of shape of cells of 𝕩
  // const auto cnt = std::accumulate(x->shape.begin() + 1, x->shape.end(), 1,
  // std::multiplies<uz>());
  int cnt = 1;
  for (int i = 1; i < x->shape.size(); i++)
    cnt *= x->shape[i];
  int i = 0;
  auto maybe_ret = CXBQN_NEW(Array, 1);
  maybe_ret->values[0] = w;
  auto warr = iswarr ? dyncast<Array>(w) : maybe_ret;
  CXBQN_DEBUG("cnt={},warr={}", cnt, CXBQN_STR_NC((O<Value>)warr));
  if (1 == nargs)
    for (; i < cnt; i++)
      ret->values[i] = x->values[i];
  else
    for (; i < cnt; i++) {
      auto xv = x->values[i];
      auto wv = warr->values[i];
      CXBQN_DEBUG("xv={},wv={},i={}", CXBQN_STR_NC(xv), CXBQN_STR_NC(wv), i);
      Args a{F, x->values[i], warr->values[i]};
      ret->values[i] = F->call(2, a);
    }

  for (; i < x->N(); i++) {
    Args a{F, x->values[i], ret->values[i - cnt]};
    ret->values[i] = F->call(2, a);
  }
  return ret;
}
} // namespace cxbqn::provides
