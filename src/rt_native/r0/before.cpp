#include <cxbqn/rt_native.hpp>

namespace cxbqn::rt_native::r0 {

O<Value> Before::call(u8 nargs, Args &args) {
  const auto f = args[4];
  const auto g = args[5];
  const auto x = args[1];
  const auto w = args[2];

  Args fargs{f, (2 == nargs ? w : x), bi_Nothing()};
  auto gw = f->call(1, fargs);

  Args gargs{g, x, gw};
  return g->call(2, gargs);
}

} // namespace cxbqn::rt_native::r0
