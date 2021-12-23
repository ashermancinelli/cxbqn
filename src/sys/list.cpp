#include "sys_helper.hpp"

namespace cxbqn::sys {
O<Value> List::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("•List: nargs={},args={}", nargs, args);
  auto d = dyncast<Array>(args[1])->to_string();
  auto ret = CXBQN_NEW(Array, 0);
  for (const auto &dd : fs::directory_iterator{d}) {
    auto fn = fs::path(dd).filename();
    if ("." == fn or ".." == fn)
      continue;
    ret->values.push_back(CXBQN_NEW(Array, fn.string()));
  }
  ret->shape[0] = ret->values.size();
  return ret;
}
} // namespace cxbqn::sys
