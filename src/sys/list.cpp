#include "sys_helper.hpp"
#include <cxbqn/array_utils.hpp>

namespace cxbqn::sys {
O<Value> List::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("•List: nargs={},args={}", nargs, args);
  auto d = to_string(args[1]);
  auto ret = CXBQN_NEW(Array);
  for (const auto &dd : fs::directory_iterator{d}) {
    auto fn = fs::path(dd).filename();
    if ("." == fn or ".." == fn)
      continue;
    ret->values.push_back(CXBQN_NEW(Array, fn.string()));
  }
  ret->shape.push_back(ret->values.size());
  return ret;
}
} // namespace cxbqn::sys
