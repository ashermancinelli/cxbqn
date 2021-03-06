#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Table::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("โ: nargs={},args={}", nargs, args);
  XNULLCHK("โ");
  auto F = args[4];

  if (t_Array != type_builtin(args[1]) or
      (nargs == 2 and t_Array != type_builtin(args[2])))
    throw std::runtime_error("โ: ๐ฉ and ๐จ must be arrays");

  // if ((1 == nargs) != (args[2]->t()[t_Nothing])) throw std::runtime_error("โ:
  // got ยท for ๐จ with 2 args, or non-ยท with 1 arg");

  auto x = dyncast<ArrayBase>(args[1]);
  if (nullptr == x)
    throw std::runtime_error("โ: ๐ฉ must be an array");

  if (1 == nargs) {
    auto ret = CXBQN_NEW(Array, x->N());
    for (int i = 0; i < x->N(); i++) {
      Args a{F, x->get(i), bi_Nothing()};
      ret->values[i] = F->call(1, a);
    }
    std::vector<uz> sh(x->shape.begin(), x->shape.end());
    ret->shape = sh;
    return ret;
  }

  auto w = dyncast<ArrayBase>(args[2]);
  if (nullptr == w)
    throw std::runtime_error("โ: ๐ฉ and ๐จ must be arrays");
  auto ret = CXBQN_NEW(Array, x->N() * w->N());
#ifdef CXBQN_STACKTRACE_DEEP
  try {
#endif
    for (int iw = 0; iw < w->N(); iw++)
      for (int ix = 0; ix < x->N(); ix++) {
        Args a{F, x->get(ix), w->get(iw)};
        ret->values[(iw * x->N()) + ix] = F->call(2, a);
      }
#ifdef CXBQN_STACKTRACE_DEEP
  } catch (std::runtime_error &e) {
    std::stringstream ss;
    ss << "โ: got '" << e.what() << "' when applying ๐ฝ";
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
} // namespace cxbqn::provides
