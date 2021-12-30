#include <cxbqn/rt_native.hpp>

namespace cxbqn::rt_native::r0 {

O<Value> Select::call(u8 nargs, Args &args) {
  const auto x = dyncast<ArrayBase>(args[1]), w = dyncast<ArrayBase>(args[2]);
  const auto xsh = x->shape;
  auto retsh = w->shape;
  const auto xrank = xsh.size();
  uz c = 1;

  if (1 != xrank) {
    for (int i = 0; i < xrank; i++)
      c *= xsh[i];
    for (int i = 1; i < xsh.size(); i++)
      retsh.push_back(xsh[i]);
  }

  auto ret = CXBQN_NEW(Array, w->N() * c);
  ret->shape = retsh;

  uz j = 0;
  for (int i=0; i < w->N(); i++) {
    const auto e = w->get(i);
    const auto m = static_cast<uz>(dyncast<Number>(e)->v);
    for (int k = 0; k < c; k++)
      ret->values[j++] = x->get(m * c + k);
  }

  return ret;
}

} // namespace cxbqn::rt_native::r0
