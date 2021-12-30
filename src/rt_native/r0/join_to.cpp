#include <cxbqn/rt_native.hpp>
#include <cxbqn/array_utils.hpp>

namespace cxbqn::rt_native::r0 {

O<Value> JoinTo::call(u8 nargs, Args &args) {
  if (1 == nargs)
    throw std::runtime_error("r0 ∾ can only take two list args");
  auto x = dyncast<ArrayBase>(args[1]);
  auto w = dyncast<ArrayBase>(args[2]);
  auto ret = CXBQN_NEW(Array);

  ret->values = values(w);
  auto xv = values(x);
  std::copy(xv.begin(), xv.end(), std::back_inserter(ret->values));

  ret->shape.assign({ret->values.size()});

  return ret;
}

} // namespace cxbqn::rt_native::r0
