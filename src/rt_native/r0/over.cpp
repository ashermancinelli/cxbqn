#include <cxbqn/rt_native.hpp>

namespace cxbqn::rt_native::r0 {

O<Value> Over::call(u8 nargs, Args &args) {
  const auto f = args[4];
  const auto g = args[5];
  const auto x = args[1];

  Args gxargs{g, x, bi_Nothing()};
  const auto gx = g->call(1, gxargs);

  Args fargs{f, gx, bi_Nothing()};

  if (2 == nargs) {
    const auto w = args[2];
    Args gwargs{g, w, bi_Nothing()};
    fargs[2] = g->call(1, gwargs);
  }

  return f->call(nargs, fargs);
}

} // namespace cxbqn::rt_native::r0
