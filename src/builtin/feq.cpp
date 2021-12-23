#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> FEQ::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("≡:nargs={},args={}", nargs, args);
  return NNC(equivilant_helper(args[1], args[2]));
}

} // namespace cxbqn::provides
