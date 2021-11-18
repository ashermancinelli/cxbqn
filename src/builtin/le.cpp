#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> LE::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("≤:nargs={},args={}", nargs, args);
  XNULLCHK("≤");
  CXBQN_LOGFLUSH();

  auto ox = args[1];
  auto ow = args[2];

  auto tx = type_builtin(ox);
  auto tw = type_builtin(ow);

  if (t_Function == tx or t_Function == tw)
    throw std::runtime_error("≤: cannot compare functions");

  auto nx = dynamic_pointer_cast<Number>(ox);
  auto nw = dynamic_pointer_cast<Number>(ow);

  return NNC(tx != tw ? tw <= tx : nw->v <= nx->v);
}
}
