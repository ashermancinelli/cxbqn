#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Range::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("↕: nargs={},args={}", nargs, args);
  XNULLCHK("↕");
  auto n = static_cast<uz>(std::dynamic_pointer_cast<Number>(args[1])->v);
  auto arr = make_shared<Array>(n);
  for (int i = 0; i < arr->N(); i++)
    arr->values[i] = make_shared<Number>(i);
  return arr;
}
}
