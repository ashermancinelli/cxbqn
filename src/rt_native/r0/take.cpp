#include <cxbqn/rt_native.hpp>

namespace cxbqn::rt_native::r0 {

O<Value> Take::call(u8 nargs, Args &args) {
  auto x = dyncast<Array>(args[1]);
  auto w = dyncast<Number>(args[2]);
  const auto l = static_cast<uz>(w->v);

  auto ret = CXBQN_NEW(Array);
  ret->values.assign(x->values.begin(), x->values.begin() + l);
  ret->shape().push_back(l);
  return ret;
}

} // namespace cxbqn::rt_native::r0
