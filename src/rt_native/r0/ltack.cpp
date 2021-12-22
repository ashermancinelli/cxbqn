#include <cxbqn/rt_native.hpp>

namespace cxbqn::rt_native::r0 {

O<Value> Ltack::call(u8 nargs, Args &args) {
  return 2 == nargs ? args[2] : args[1];
}

} // namespace cxbqn::rt_native::r0
