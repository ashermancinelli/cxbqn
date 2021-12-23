#include <cxbqn/rt_native.hpp>

namespace cxbqn::rt_native::r0 {

O<Value> Each::call(u8 nargs, Args &args) {
  auto f = args[4];
  auto x = dyncast<Array>(args[1]);
  auto w = dyncast<Array>(args[2]);

  const auto l = x->N();
  auto ret = CXBQN_NEW(Array, l);
  ret->shape = x->shape;
  for (int i = 0; i < l; i++) {
    Args a{f, x->values[i], w->values[i]};
    ret->values[i] = f->call(2, a);
  }

  return ret;
}

} // namespace cxbqn::rt_native::r0
