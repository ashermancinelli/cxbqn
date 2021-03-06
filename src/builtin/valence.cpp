#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Valence::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("⊘: nargs={},args={}", nargs, args);
  XNULLCHK("⊘");
  CXBQN_LOGFLUSH();
  auto x = args[1];
  auto w = args[2];
  auto m = args[3];
  auto f = args[4];
  auto g = args[5];
  Args a1{f, x, bi_Nothing()}, a2{g, x, w};
  return 1 == nargs ? f->call(1, a1) : g->call(2, a2);
}

} // namespace cxbqn::provides
