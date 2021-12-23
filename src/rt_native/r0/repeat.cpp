#include <cxbqn/rt_native.hpp>

namespace cxbqn::rt_native::r0 {

O<Value> Repeat::call(u8 nargs, Args &args) {
  const auto f = args[4];
  const auto g = args[5];
  const auto x = args[1];
  const auto w = args[2];

  Args gargs{g, x, w};
  auto gret = g->call(nargs, gargs);

  if (0.0 == dyncast<Number>(gret)->v)
    return x;

  Args fargs{f, x, w};
  return f->call(nargs, fargs);
}

} // namespace cxbqn::rt_native::r0
