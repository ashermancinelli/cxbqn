#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Root::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("√:nargs={},args={}", nargs, args);
  XNULLCHK("√");
  auto ox = args[1];
  auto ow = args[2];
  if (auto foo = dyncast<Character>(ox))
    throw std::runtime_error("√: only numbers");
  if (t_Number != type_builtin(ox))
    throw std::runtime_error("√: only numbers");
  auto x = dyncast<Number>(ox);
  auto w = dyncast<Number>(ow);
  return NN(2 == nargs ? std::pow(x->v, 1 / w->v) : std::sqrt(x->v));
}

} // namespace cxbqn::provides
