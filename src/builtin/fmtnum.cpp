#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> FmtNum::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("•FmtNum:nargs={},args={}", nargs, args);
  XNULLCHK("•FmtNum");
  auto x = std::dynamic_pointer_cast<Number>(args[1]);
  std::stringstream ss;
  if (x->v == std::numeric_limits<f64>::infinity())
    ss << "∞";
  else if(x->v == -std::numeric_limits<f64>::infinity())
    ss << "¯∞";
  else
    ss << x->v;
  auto s = ss.str();
  auto ret = make_shared<Array>(0);
  for (auto it = s.begin(); it != s.end();)
    ret->values.push_back(make_shared<Character>(utf8::next(it, s.end())));
  ret->shape[0] = ret->values.size();
  return ret;
}

} // namespace cxbqn::provides
