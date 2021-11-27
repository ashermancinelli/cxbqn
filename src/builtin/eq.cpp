#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> EQ::call(u8 nargs, Args args) {
  CXBQN_DEBUG("=:nargs={},args={}", nargs, args);
  XNULLCHK("=");
  CXBQN_LOGFLUSH();
  auto ox = args[1];
  auto ow = args[2];

  if (1 == nargs)
    if (auto x = dyncast<Array>(ox))
      return NNC(x->shape.size());
    else
      return NNC(0);

  return NNC(eq_recursive(ox, ow));
}
}
