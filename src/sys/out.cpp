#include "sys_helper.hpp"
#include <cstdio>
namespace cxbqn::sys {

O<Value> Out::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("Out: nargs={},args={}", nargs, args);
  std::string end = 2 == nargs ? dyncast<Array>(args[2])->to_string() : "\n";
  auto x = dyncast<Array>(args[1]);
  if (nullptr == x)
    throw std::runtime_error("•Out: can only be called with strings");

  fmt::print("{}{}", x->to_string(), end);
  std::fflush(stdout);

  return x;
}

} // namespace cxbqn::sys
