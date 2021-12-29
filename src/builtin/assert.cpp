#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Assert::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("!: nargs={},args={}", nargs, args);
  XNULLCHK("!");
  auto x = args[1], w = args[2];
  if (t_Number != type_builtin(args[1]) or
      !feq_helper(1., dyncast<Number>(args[1])->v)) {
    std::string s = "";
    if (nargs == 2) {
      if (type_builtin(w) == t_Array)
        s += to_string(w);
      else
        s += fmt::format("{}", CXBQN_STR_NC(w));
    }
    s += " ! ";
    if (t_Array == type_builtin(args[1])) {
      auto ar = dyncast<Array>(args[1]);

    } else
      s += fmt::format("{}", CXBQN_STR_NC(args[1]));
    CXBQN_CRIT("{}", s);
    throw std::runtime_error(s);
  }
  return args[1];
}

} // namespace cxbqn::provides
