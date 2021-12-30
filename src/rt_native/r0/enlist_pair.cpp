#include <cxbqn/rt_native.hpp>

namespace cxbqn::rt_native::r0 {

O<Value> EnlistPair::call(u8 nargs, Args &args) {
  auto ret = CXBQN_NEW(Array);
  ret->shape.push_back(1);
  if (2 == nargs) {
    ret->shape[0]++;
    ret->values.push_back(args[2]);
  }
  ret->values.push_back(args[1]);
  return ret;
}

} // namespace cxbqn::rt_native::r0
