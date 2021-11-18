#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> FNE::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("≢:nargs={},args={}", nargs, args);
  XNULLCHK("≢");
  if (2 == nargs)
    throw std::runtime_error("≢: provided function expected only one arg");
  auto arr = std::dynamic_pointer_cast<Array>(args[1]);
  auto ret = make_shared<Array>(arr->shape.size());
  for (int i = 0; i < ret->N(); i++)
    ret->values[i] = make_shared<Number>(static_cast<f64>(arr->shape[i]));
  return ret;
}
}
