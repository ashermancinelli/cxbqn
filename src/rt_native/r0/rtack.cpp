#include <cxbqn/rt_native.hpp>

namespace cxbqn::rt_native::r0 {

O<Value> Rtack::call(u8 nargs, Args &args) { return args[1]; }

} // namespace cxbqn::rt_native::r0
