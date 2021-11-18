#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> PrimInd::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("PrimInd: nargs={},args={}", nargs, args);
  XNULLCHK("•PrimInd");

  if (2 == nargs)
    throw std::runtime_error("PrimInd: expected one argument, got two");

  auto x = args[1];
  auto it = std::find(runtime.begin(), runtime.end(), x);
  if (it == runtime.end()) {
    return NNC(runtime.size());
  }

  return NNC(std::distance(runtime.begin(), it));
}
}
