#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Table::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("⌜: nargs={},args={}", nargs, args);
  XNULLCHK("⌜");
  auto F = args[4];

  if (t_Array != type_builtin(args[1]) or t_Array != type_builtin(args[2]))
    throw std::runtime_error("⌜: 𝕩 and 𝕨 must be arrays");

  // if ((1 == nargs) != (args[2]->t()[t_Nothing])) throw std::runtime_error("⌜:
  // got · for 𝕨 with 2 args, or non-· with 1 arg");

  auto x = dyncast<Array>(args[1]);
  if (nullptr == x)
    throw std::runtime_error("⌜: 𝕩 must be an array");
  const auto &xv = x->values;

  if (1 == nargs) {
    auto ret = CXBQN_NEW(Array, x->N());
    for (int i = 0; i < x->N(); i++)
      ret->values[i] = F->call(1, {F, x->values[i], bi_Nothing()});
    ret->shape = x->shape;
    return ret;
  }

  auto w = dyncast<Array>(args[2]);
  if (nullptr == w)
    throw std::runtime_error("⌜: 𝕩 and 𝕨 must be arrays");
  const auto &wv = w->values;
  auto ret = CXBQN_NEW(Array, x->N() * w->N());
#ifdef CXBQN_STACKTRACE_DEEP
  try {
#endif
    for (int iw = 0; iw < w->N(); iw++)
      for (int ix = 0; ix < x->N(); ix++) {
        ret->values[(iw * x->N()) + ix] = F->call(2, {F, xv[ix], wv[iw]});
      }
#ifdef CXBQN_STACKTRACE_DEEP
  } catch (std::runtime_error &e) {
    std::stringstream ss;
    ss << "⌜: got '" << e.what() << "' when applying 𝔽";
    throw ss.str();
  }
#endif
  ret->shape.clear();
  for (const auto i : w->shape)
    ret->shape.push_back(i);
  for (const auto i : x->shape)
    ret->shape.push_back(i);

  return ret;
}
}
