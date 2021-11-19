#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Assert::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("!: nargs={},args={}", nargs, args);
  XNULLCHK("!");
  auto x = args[1], w = args[2];
  if (t_Number != type_builtin(args[1]) or
      !feq_helper(1., std::dynamic_pointer_cast<Number>(args[1])->v)) {
    std::string s = "";
    if (nargs == 2) {
      if (type_builtin(w) == t_Array)
        s += dynamic_pointer_cast<Array>(w)->to_string();
      else
        s += fmt::format("{}", CXBQN_STR_NC(w));
    }
    s += fmt::format(" ! {}", CXBQN_STR_NC(args[1]));
    CXBQN_CRIT("{}", s);
    throw std::runtime_error(s);
  }
  return args[1];
}

} // namespace cxbqn::provides
