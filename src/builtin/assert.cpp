#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Assert::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("!: nargs={},args={}", nargs, args);
  XNULLCHK("!");
  auto x = args[1], w = args[2];
  if (t_Number != type_builtin(args[1]) or
      !feq_helper(1., dyncast<Number>(args[1])->v)) {
    std::stringstream ss;
    if (nargs == 2) {
      ss << "? ";
      //w->repr(ss);
      //ss << " ";
    }
    ss << "! ";
    x->repr(ss);
    CXBQN_CRIT("{}", ss.str());
    throw std::runtime_error(ss.str());
  }
  return args[1];
}

} // namespace cxbqn::provides
