#include <cxbqn/rt_native.hpp>

namespace cxbqn::rt_native::r0 {

O<Value> JoinTo::call(u8 nargs, Args &args) {
  if (1 == nargs)
    throw std::runtime_error("r0 ∾ can only take two list args");
  auto x = dyncast<Array>(args[1]);
  auto w = dyncast<Array>(args[2]);
  auto ret = CXBQN_NEW(Array);

  std::copy(w->values.begin(), w->values.end(), std::back_inserter(ret->values));
  std::copy(x->values.begin(), x->values.end(), std::back_inserter(ret->values));
  ret->shape.assign({ret->values.size()});

  return ret;
}

} // namespace cxbqn::rt_native::r0
