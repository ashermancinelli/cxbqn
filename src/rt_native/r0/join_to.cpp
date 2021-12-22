#include <cxbqn/rt_native.hpp>

namespace cxbqn::rt_native::r0 {

O<Value> JoinTo::call(u8 nargs, Args &args) {
  auto x = dyncast<Array>(args[1]);
  auto w = dyncast<Array>(args[2]);
  std::copy(x->values.begin(), x->values.end(), std::back_inserter(w->values));
  w->shape.assign({w->values.size()});
  return w;
}

} // namespace cxbqn::rt_native::r0
