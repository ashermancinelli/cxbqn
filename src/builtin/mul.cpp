#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Mul::call(u8 nargs, Args args) {
  CXBQN_DEBUG("×:nargs={},args={}", nargs, args);
  XNULLCHK("×");
  auto ox = args[1];
  auto ow = args[2];
  auto x = dyncast<Number>(args[1]);
  auto w = dyncast<Number>(args[2]);
  if (t_Number != type_builtin(ox) || t_Number != type_builtin(ow))
    throw std::runtime_error("×: arguments must be numbers");
  if (2 == nargs)
    return NN(w->v * x->v);
  return NN(feq_helper(0.0, x->v) ? 0 : x->v > 0 ? 1 : 0);
}
} // namespace cxbqn::provides
