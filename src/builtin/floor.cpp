#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Floor::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("⌊:nargs={},args={}", nargs, args);
  XNULLCHK("⌊");
  auto ox = args[1];
  auto ow = args[2];
  if (t_Number != type_builtin(ox))
    throw std::runtime_error("⌊: only numbers");
  auto x = dyncast<Number>(ox);
  auto w = dyncast<Number>(ow);
  return NN(2 == nargs ? std::min(w->v, x->v) : std::floor(x->v));
}

} // namespace cxbqn::provides
