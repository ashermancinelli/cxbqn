#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Type::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("•Type:nargs={},args={}", nargs, args);
  XNULLCHK("•Type");
  auto r = NNC(type_builtin(args[1]));
  return r;
}

} // namespace cxbqn::provides
