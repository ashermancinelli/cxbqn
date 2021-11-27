#include "sys_helper.hpp"
namespace cxbqn::sys {

O<Value> Out::call(u8 nargs, Args args) {
  CXBQN_DEBUG("Out: nargs={},args={}", nargs, args);
  if (2 == nargs)
    throw std::runtime_error("•Out: can only be called with one arg");

  auto x = dyncast<Array>(args[1]);
  if (nullptr == x)
    throw std::runtime_error("•Out: can only be called with strings");

  fmt::print("{}\n", x->to_string());

  return x;
}

}

