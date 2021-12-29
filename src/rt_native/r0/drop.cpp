#include <cxbqn/rt_native.hpp>

namespace cxbqn::rt_native::r0 {

O<Value> Drop::call(u8 nargs, Args &args) {
  auto x = dyncast<Array>(args[1]);
  auto w = dyncast<Number>(args[2]);

  auto ret = CXBQN_NEW(Array);
  ret->values.assign(x->values.begin() + static_cast<uz>(w->v),
                     x->values.end());
  ret->shape.push_back(ret->values.size());
  return ret;
}

} // namespace cxbqn::rt_native::r0
