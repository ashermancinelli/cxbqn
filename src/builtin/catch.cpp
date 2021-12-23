#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Catch::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("⎊: nargs={},args={}", nargs, args);
  XNULLCHK("⎊");
  try {
    auto F = args[4];
    Args a{F, args[1], args[2]};
    auto ret = F->call(nargs, a);
    return ret;
  } catch (std::runtime_error &e) {
    auto G = args[5];
    Args a{G, args[1], args[2]};
    auto ret = G->call(nargs, a);
    return ret;
  }
}

} // namespace cxbqn::provides
