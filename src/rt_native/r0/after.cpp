#include <cxbqn/rt_native.hpp>

namespace cxbqn::rt_native::r0 {

O<Value> After::call(u8 nargs, Args &args) {
  const auto f = args[4];
  const auto g = args[5];
  const auto x = args[1];
  const auto w = args[2];

  Args gargs{g, x, bi_Nothing()};
  auto fx = g->call(1, gargs);

  Args fargs{f, fx, (2 == nargs ? w : x)};
  return f->call(2, fargs);
}

} // namespace cxbqn::rt_native::r0
