#include <cxbqn/rt_native.hpp>

namespace cxbqn::rt_native::r0 {

O<Value> EnlistPair::call(u8 nargs, Args &args) {
  auto ret = CXBQN_NEW(Array);
  if (2 == nargs)
    ret->values.push_back(args[2]);
  ret->values.push_back(args[1]);
  ret->shape().push_back(ret->values.size());
  return ret;
}

} // namespace cxbqn::rt_native::r0
