#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Assert::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("!: nargs={},args={}", nargs, args);
  // fmt::print("!: nargs={},args={}\n", nargs, args);
  XNULLCHK("!");
  bool shoulddie = false;
  if (t_Number != type_builtin(args[1]))
    shoulddie = true;
  if (!feq_helper(1., std::dynamic_pointer_cast<Number>(args[1])->v))
    shoulddie = true;
  if (shoulddie) {
    const auto s =
        fmt::format("{} ! {}", (2 == nargs ? CXBQN_STR_NC(args[2]) : ""),
                    CXBQN_STR_NC(args[1]));
    CXBQN_CRIT("{}", s);
    throw std::runtime_error(s);
  }
  return args[1];
}

}
