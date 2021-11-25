#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Minus::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("-: nargs={},args={}", nargs, args);
  XNULLCHK("-");
  auto ox = args[1];
  auto ow = args[2];
  auto x = dyncast<Number>(args[1]);
  auto w = dyncast<Number>(args[2]);

  if (t_Character == type_builtin(ow) and t_Number == type_builtin(ox)) {
    return check_char(make_shared<Character>(w->v - x->v));
  }
  if (t_Character == type_builtin(ow) and t_Character == type_builtin(ox)) {
    return make_shared<Number>(w->v - x->v);
  }
  if (t_Number != type_builtin(ox))
    throw std::runtime_error("-: can only negate numbers");

  return NN(2 == nargs ? w->v - x->v : -x->v);
}

} // namespace cxbqn::provides
