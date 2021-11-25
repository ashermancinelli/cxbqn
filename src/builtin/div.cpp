#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Div::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("÷:nargs={},args={}", nargs, args);
  XNULLCHK("÷");
  auto ox = args[1];
  auto ow = args[2];
  if (t_Number != type_builtin(ox))
    throw std::runtime_error("÷: only numbers");
  auto x = dyncast<Number>(ox);
  auto w = dyncast<Number>(ow);
  return CXBQN_NEW(Number, 2 == nargs ? w->v / x->v : 1 / x->v);
}

}
