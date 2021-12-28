#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Shape::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("≢: nargs={},args={}", nargs, args);
  XNULLCHK("≢");
  auto ret = CXBQN_NEW(Array);
  auto sh = dyncast<Array>(args[1])->shape();
  ret->values.resize(sh.size());
  for (int i = 0; i < sh.size(); i++)
    ret->values[i] = CXBQN_NEW(Number, sh[i]);
  return ret;
}
} // namespace cxbqn::provides
