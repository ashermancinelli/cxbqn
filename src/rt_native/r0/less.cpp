#include <cxbqn/rt_native.hpp>

namespace cxbqn::rt_native::r0 {

O<Value> Less::call(u8 nargs, Args &args) {
  const auto x = args[1];
  const auto w = args[2];

  if (2 == nargs) {
    const auto xx = dyncast<Number>(x)->v;
    const auto ww = dyncast<Number>(w)->v;

    const auto tx = type_builtin(x), tw = type_builtin(w);

    return CXBQN_NEW(Number, (tx == tw ? ww < xx : tw < tx));
  } else {
    // leave shape as []
    auto ret = CXBQN_NEW(Array);
    ret->values.push_back(x);
    return ret;
  }
}

} // namespace cxbqn::rt_native::r0
