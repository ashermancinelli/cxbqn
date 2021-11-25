#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> ArrayDepth::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("≢: nargs={},args={}", nargs, args);
  XNULLCHK("≢");
  return CXBQN_NEW(Number, static_cast<f64>(array_depth_helper(0, args[1])));
}
}
