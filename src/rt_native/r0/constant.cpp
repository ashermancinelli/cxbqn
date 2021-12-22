#include <cxbqn/rt_native.hpp>

namespace cxbqn::rt_native::r0 {

O<Value> Constant::call(u8 nargs, Args &args) {
  return args[4];
}

} // namespace cxbqn::rt_native::r0
