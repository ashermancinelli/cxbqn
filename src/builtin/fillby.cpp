#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> FillBy::call(u8 nargs, Args& args) {
  CXBQN_DEBUG("_fillBy_: nargs={},args={}", nargs, args);
  XNULLCHK("_fillBy_");
  auto F = args[4];
  Args a{F, args[1], args[2]};
  return F->call(nargs, a);
}

}
