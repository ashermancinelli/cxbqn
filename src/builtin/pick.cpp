#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Pick::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("⊑: nargs={},args={}", nargs, args);
  XNULLCHK("⊑");
  auto n = static_cast<uz>(dyncast<Number>(args[2])->v);
  return dyncast<ArrayBase>(args[1])->get(n);
}

} // namespace cxbqn::provides
