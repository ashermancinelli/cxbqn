#include "sys_helper.hpp"
namespace cxbqn::sys {

O<Value> BQN::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("•BQN: nargs={},args={}", nargs, args);

  auto x = dynamic_pointer_cast<Array>(args[1]);
  if (!x)
    throw std::runtime_error("•BQN: 𝕩 must be a string");

  auto compiled = _compiler->call(2, {_compiler, x, _compiler_args});

  auto ret = vm::run(compiled);

  return ret.v;
}

} // namespace cxbqn::sys
