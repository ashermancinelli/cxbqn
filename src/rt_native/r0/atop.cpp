#include <cxbqn/rt_native.hpp>

namespace cxbqn::rt_native::r0 {

O<Value> Atop::call(u8 nargs, Args &args) {
  const auto f = args[4];
  const auto g = args[5];
  const auto x = args[1];
  const auto w = args[2];

  O<Value> gret;

  if (2 == nargs) {
    Args gargs{g, x, w};
    gret = g->call(2, gargs);
  } else {
    Args gargs{g, x, bi_Nothing()};
    gret = g->call(1, gargs);
  }

  Args fargs{f, gret, bi_Nothing()};
  auto fret = f->call(1, fargs);
  return fret;
}

} // namespace cxbqn::rt_native::r0
