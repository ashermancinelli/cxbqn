#include <cxbqn/rt_native.hpp>
#include <cxbqn/array_utils.hpp>

namespace cxbqn::rt_native::r0 {

O<Value> Drop::call(u8 nargs, Args &args) {
  auto x = dyncast<ArrayBase>(args[1]);
  auto w = dyncast<Number>(args[2]);

  auto ret = CXBQN_NEW(Array);
  auto vs = values(x);
  ret->values.assign(vs.begin() + static_cast<uz>(w->v), vs.end());
  ret->shape.push_back(ret->values.size());
  return ret;
}

} // namespace cxbqn::rt_native::r0
