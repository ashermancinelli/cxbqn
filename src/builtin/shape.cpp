#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Shape::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("≢: nargs={},args={}", nargs, args);
  XNULLCHK("≢");
  auto ret = make_shared<Array>();
  auto sh = std::dynamic_pointer_cast<Array>(args[1])->shape;
  ret->values.resize(sh.size());
  for (int i = 0; i < sh.size(); i++)
    ret->values[i] = make_shared<Number>(sh[i]);
  return ret;
}
}
