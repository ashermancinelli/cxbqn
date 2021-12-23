#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Plus::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("+:nargs={},args={}", nargs, args);
  XNULLCHK("+");
  auto ox = args[1];
  auto ow = args[2];
  if (1 == nargs)
    return ox;

  /* compare by value for data types */
  auto x = dyncast<Number>(ox);
  auto w = dyncast<Number>(ow);

  if (t_Character == type_builtin(ox) and t_Character == type_builtin(ow))
    throw std::runtime_error("+: Cannot add two characters");
  if (!ox->t()[t_DataValue] or !ow->t()[t_DataValue]) {
    CXBQN_CRIT("Got x={}, w={}", CXBQN_STR_NC(ox), CXBQN_STR_NC(ow));
    throw std::runtime_error("+: Cannot add non-data values.");
  }
  if (t_Character == type_builtin(ox) || t_Character == type_builtin(ow)) {
    return check_char(CXBQN_NEW(Character, x->v + w->v));
  }
  return NN(x->v + w->v);
}
} // namespace cxbqn::provides
