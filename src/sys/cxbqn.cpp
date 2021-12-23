#include "sys_helper.hpp"
namespace cxbqn::sys {
O<Value> CXBQN::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("•CXBQN: nargs={},args={}", nargs, args);
  return CXBQN_NEW(Number, 1);
}
} // namespace cxbqn::sys
