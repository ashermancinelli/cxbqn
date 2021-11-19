#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Type::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("•Type:nargs={},args={}", nargs, args);
  fmt::print("•Type:nargs={},args={}\n", nargs, args);
  XNULLCHK("•Type");
  auto r = NNC(type_builtin(args[1]));
  fmt::print("{}\n", CXBQN_STR_NC(O<Value>(r)));
  return r;
}

}
