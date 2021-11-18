#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Pick::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("⊑: nargs={},args={}", nargs, args);
  XNULLCHK("⊑");
  auto n = static_cast<uz>(std::dynamic_pointer_cast<Number>(args[2])->v);
  return std::dynamic_pointer_cast<Array>(args[1])->values[n];
}

}
