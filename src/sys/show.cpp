#include "sys_helper.hpp"
namespace cxbqn::sys {

O<Value> Show::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("Show: nargs={},args={}", nargs, args);
  if (2 == nargs)
    throw std::runtime_error("•Show: can only be called with one arg");

  auto x = dynamic_pointer_cast<Array>(args[1]);
  if (nullptr == x)
    throw std::runtime_error("•Show: can only be called with strings");

  auto s = x->to_string();
  fmt::print("{}\n", s);

  return x;
}

}

