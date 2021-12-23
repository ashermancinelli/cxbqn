#include "sys_helper.hpp"
namespace cxbqn::sys {

O<Value> Show::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("Show: nargs={},args={}", nargs, args);
  if (2 == nargs)
    throw std::runtime_error("•Show: can only be called with one arg");

  auto x = args[1];

  Args a{_fmt, x, bi_Nothing()};
  auto formatted = _fmt->call(1, a);
  fmt::print("{}\n", dyncast<Array>(formatted)->to_string());

  return formatted;
}

} // namespace cxbqn::sys
