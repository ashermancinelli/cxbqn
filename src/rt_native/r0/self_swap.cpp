#include <cxbqn/rt_native.hpp>

namespace cxbqn::rt_native::r0 {

O<Value> SelfSwap::call(u8 nargs, Args &args) {
  auto *f = args[4];
  Args a{f, (2 == nargs ? args[2] : args[1]), args[1]};
  return f->call(2, a);
}

} // namespace cxbqn::rt_native::r0
