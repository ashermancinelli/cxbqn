#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Div::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("÷:nargs={},args={}", nargs, args);
  XNULLCHK("÷");
  auto ox = args[1];
  auto ow = args[2];
  if (t_Number != type_builtin(ox))
    throw std::runtime_error("÷: only numbers");
  auto x = std::dynamic_pointer_cast<Number>(ox);
  auto w = std::dynamic_pointer_cast<Number>(ow);
  return make_shared<Number>(2 == nargs ? w->v / x->v : 1 / x->v);
}

}
