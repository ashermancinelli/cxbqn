#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Catch::call(u8 nargs, Args args) {
  CXBQN_DEBUG("⎊: nargs={},args={}", nargs, args);
  XNULLCHK("⎊");
  try {
    auto F = args[4];
    auto ret = F->call(nargs, {F, args[1], args[2]});
    return ret;
  } catch (std::runtime_error &e) {
    auto G = args[5];
    auto ret = G->call(nargs, {G, args[1], args[2]});
    return ret;
  }
}

}
