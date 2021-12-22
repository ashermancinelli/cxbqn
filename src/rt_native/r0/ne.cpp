#include <cxbqn/rt_native.hpp>

namespace cxbqn::rt_native::r0 {

O<Value> NE::call(u8 nargs, Args &args) {
  auto x = args[1];
  auto ret = t_Array == type_builtin(x) ? dyncast<Array>(x)->shape[0] : 1;
  return CXBQN_NEW(Number, ret);
}

} // namespace cxbqn::rt_native::r0
