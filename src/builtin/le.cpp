#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> LE::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("≤:nargs={},args={}", nargs, args);
  XNULLCHK("≤");
  CXBQN_LOGFLUSH();

  auto ox = args[1];
  auto ow = args[2];

  auto tx = type_builtin(ox);
  auto tw = type_builtin(ow);

  if (t_Function == tx or t_Function == tw)
    throw std::runtime_error("≤: cannot compare functions");

  auto nx = dyncast<Number>(ox);
  auto nw = dyncast<Number>(ow);

  return NNC(tx != tw ? tw <= tx : nw->v <= nx->v);
}
} // namespace cxbqn::provides
