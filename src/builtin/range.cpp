#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Range::call(u8 nargs, Args args) {
  CXBQN_DEBUG("↕: nargs={},args={}", nargs, args);
  XNULLCHK("↕");
  auto n = static_cast<uz>(dyncast<Number>(args[1])->v);
  auto arr = CXBQN_NEW(Array, n);
  for (int i = 0; i < arr->N(); i++)
    arr->values[i] = CXBQN_NEW(Number, i);
  return arr;
}
}
