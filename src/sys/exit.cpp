#include "sys_helper.hpp"
namespace cxbqn::sys {
O<Value> Exit::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("•CXBQN: nargs={},args={}", nargs, args);
  auto n = dynamic_pointer_cast<Number>(args[1])->v;
  std::exit(n);
}
}
