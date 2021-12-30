#include <cxbqn/rt_native.hpp>
#include <cxbqn/array_utils.hpp>

namespace cxbqn::rt_native::r0 {

O<Value> Each::call(u8 nargs, Args &args) {
  auto f = args[4];
  auto x = dyncast<ArrayBase>(args[1]);
  auto w = dyncast<ArrayBase>(args[2]);

  const auto l = x->N();
  auto ret = CXBQN_NEW(Array, l);
  ret->shape = x->shape;

  auto xv = values(x);
  auto wv = values(w);
  for (int i = 0; i < l; i++) {
    Args a{f, xv[i], wv[i]};
    ret->values[i] = f->call(2, a);
  }

  return ret;
}

} // namespace cxbqn::rt_native::r0
