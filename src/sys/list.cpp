#include "sys_helper.hpp"

namespace cxbqn::sys {
O<Value> List::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("•List: nargs={},args={}", nargs, args);
  auto d = dyncast<Array>(args[1])->to_string();
  auto ret = make_shared<Array>(0);
  for (const auto& dd : fs::directory_iterator{d}) {
    auto fn = fs::path(dd).filename();
    if ("." == fn or ".." == fn) continue;
    ret->values.push_back(make_shared<Array>(fn.string()));
  }
  ret->shape[0] = ret->values.size();
  return ret;
}
}
