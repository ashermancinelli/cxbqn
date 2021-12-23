#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> FNE::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("≢:nargs={},args={}", nargs, args);
  XNULLCHK("≢");
  if (2 == nargs)
    throw std::runtime_error("≢: provided function expected only one arg");
  auto arr = dyncast<Array>(args[1]);
  auto ret = CXBQN_NEW(Array, arr->shape.size());
  for (int i = 0; i < ret->N(); i++)
    ret->values[i] = CXBQN_NEW(Number, static_cast<f64>(arr->shape[i]));
  return ret;
}
} // namespace cxbqn::provides
