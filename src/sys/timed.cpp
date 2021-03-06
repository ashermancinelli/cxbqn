#include "sys_helper.hpp"
#include <chrono>

namespace cxbqn::sys {

template <class result_t = std::chrono::milliseconds,
          class clock_t = std::chrono::steady_clock,
          class duration_t = std::chrono::milliseconds>
auto since(std::chrono::time_point<clock_t, duration_t> const &start) {
  return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}

O<Value> Timed::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("•_timed: nargs={},args={}", nargs, args);
  auto F = args[4];
  auto x = args[1];
  auto w = args[2];

  uz cnt = 2 == nargs ? static_cast<uz>(dyncast<Number>(w)->v) : 1;

  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < cnt; i++) {
    Args a{F, x, bi_Nothing()};
    F->call(1, a);
  }
  auto stop = std::chrono::high_resolution_clock::now();
  auto dur =
      std::chrono::duration_cast<std::chrono::seconds>(stop - start).count();

  return CXBQN_NEW(Number, static_cast<f64>(dur));
}

} // namespace cxbqn::sys
