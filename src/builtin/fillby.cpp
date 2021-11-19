#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> FillBy::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("_fillBy_: nargs={},args={}", nargs, args);
  XNULLCHK("_fillBy_");
  auto F = args[4];
  return F->call(nargs, {F, args[1], args[2]});
}

}
