#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> FmtNum::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("•FmtNum:nargs={},args={}", nargs, args);
  XNULLCHK("•FmtNum");
  auto x = dyncast<Number>(args[1]);
  std::stringstream ss;
  if (x->v == std::numeric_limits<f64>::infinity())
    ss << "∞";
  else if (x->v == -std::numeric_limits<f64>::infinity())
    ss << "¯∞";
  else
    ss << x->v;
  auto s = ss.str();
  auto ret = CXBQN_NEW(Array);
  for (auto it = s.begin(); it != s.end();)
    ret->values.push_back(CXBQN_NEW(Character, utf8::next(it, s.end())));
  ret->shape().push_back(ret->values.size());
  return ret;
}

} // namespace cxbqn::provides
