#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> FmtNum::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("•FmtNum:nargs={},args={}", nargs, args);
  XNULLCHK("•FmtNum");
  auto x = std::dynamic_pointer_cast<Number>(args[1]);
  auto s = fmt::format("{}", x->v);
  auto ret = make_shared<Array>(s.size());
  for (auto c : s)
    ret->values.push_back(make_shared<Character>(c));
  return ret;
}

} // namespace cxbqn::provides
