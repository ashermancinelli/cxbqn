#include "sys_helper.hpp"
#include <cxbqn/array_utils.hpp>
#include <cstdio>
namespace cxbqn::sys {

O<Value> Out::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("Out: nargs={},args={}", nargs, args);
  std::string end = 2 == nargs ? to_string(args[2]) : "\n";
  auto x = dyncast<Array>(args[1]);
  if (nullptr == x)
    throw std::runtime_error("•Out: can only be called with strings");

  fmt::print("{}{}", to_string(x), end);
  std::fflush(stdout);

  return x;
}

} // namespace cxbqn::sys
