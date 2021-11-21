#include "sys_helper.hpp"
namespace cxbqn::sys {

O<Value> Out::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("Out: nargs={},args={}", nargs, args);
  if (2 == nargs)
    throw std::runtime_error("•Out: can only be called with one arg");

  auto x = args[1];

  auto formatted = _fmt->call(1, {_fmt, x, bi_Nothing()});
  fmt::print("{}\n", dynamic_pointer_cast<Array>(formatted)->to_string());

  return formatted;
}

}

