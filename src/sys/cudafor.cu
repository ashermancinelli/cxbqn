#include "sys_helper.hpp"
namespace cxbqn::sys {
O<Value> CUDAFor::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("•_CUDAFor: nargs={},args={}", nargs, args);
  return CXBQN_NEW(Number, 1);
}
}
