#include "sys_helper.hpp"
#include <chrono>

namespace cxbqn::sys {

O<Value> UnixTime::call(u8 nargs, Args &args) {
  using namespace std::chrono;
  CXBQN_DEBUG("•UnixTime: nargs={},args={}", nargs, args);
  auto now = system_clock::now();
  auto dur = duration_cast<seconds>(now.time_since_epoch()).count();
  return CXBQN_NEW(Number, static_cast<f64>(dur));
}

} // namespace cxbqn::sys
