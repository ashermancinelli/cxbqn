#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Scan::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("`: nargs={},args={}", nargs, args);
  XNULLCHK("`");
  if (t_Array != type_builtin(args[1]))
    throw std::runtime_error("`: 𝕩 must have rank at least 1");

  // if ((1 == nargs) != (args[2]->t()[t_Nothing])) throw std::runtime_error("`:
  // got · for 𝕨 with 2 args, or non-· with 1 arg");

  auto x = dyncast<ArrayBase>(args[1]);

  if (x->N() == 0) {
    if (1 == x->shape.size() and 0 == x->shape.back())
      return CXBQN_NEW(Array, 0);
    auto ret = CXBQN_NEW(Array, 0);
    ret->shape = x->shape;
  }

  auto w = args[2];
  auto F = args[4];

  auto sh = x->shape;
  auto iswarr = (t_Array == type_builtin(w));
  if (2 == nargs) {
    auto w_rank = iswarr ? dyncast<ArrayBase>(w)->shape.size() : 0;
    if (1 + w_rank != sh.size())
      throw std::runtime_error("`: rank of 𝕨 must be cell rank of 𝕩");
    if (iswarr) {
      const auto &wsh = dyncast<ArrayBase>(w)->shape;
      for (int i = 0; i < sh.size() - 1; i++)
        if (wsh[i] != sh[i + 1])
          throw std::runtime_error("`: shape of 𝕨 must be cell shape of 𝕩");
    }
  }

  auto ret = CXBQN_NEW(Array);
  ret->values.resize(x->N());
  ret->shape = sh;

  // product reduction of shape of cells of 𝕩
  // const auto cnt = std::accumulate(x->shape.begin() + 1, x->shape.end(), 1,
  // std::multiplies<uz>());
  int cnt = 1;
  for (int i = 1; i < sh.size(); i++)
    cnt *= sh[i];
  int i = 0;
  auto maybe_ret = CXBQN_NEW(Array, 1);
  maybe_ret->values[0] = w;
  auto warr = iswarr ? dyncast<ArrayBase>(w) : maybe_ret;
  CXBQN_DEBUG("cnt={},warr={}", cnt, CXBQN_STR_NC((O<Value>)warr));
  if (1 == nargs)
    for (; i < cnt; i++)
      ret->values[i] = x->get(i);
  else
    for (; i < cnt; i++) {
      auto xv = x->get(i);
      auto wv = warr->get(i);
      CXBQN_DEBUG("xv={},wv={},i={}", CXBQN_STR_NC(xv), CXBQN_STR_NC(wv), i);
      Args a{F, x->get(i), warr->get(i)};
      ret->values[i] = F->call(2, a);
    }

  for (; i < x->N(); i++) {
    Args a{F, x->get(i), ret->values[i - cnt]};
    ret->values[i] = F->call(2, a);
  }
  return ret;
}
} // namespace cxbqn::provides
