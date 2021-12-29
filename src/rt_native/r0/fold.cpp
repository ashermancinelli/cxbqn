#include <cxbqn/rt_native.hpp>
#include <sstream>

namespace cxbqn::rt_native::r0 {

O<Value> Fold::call(u8 nargs, Args &args) {
  const auto f = args[4];
  const auto x = dyncast<Array>(args[1]);
  const auto w = args[2];

  {
    auto const sh = x->shape;
    if (0 == sh.size() or (1 == sh.size() and 0 == sh[0]))
      return CXBQN_NEW(Array);
  }

  auto l = x->shape[0];

  auto r = 2 == nargs ? w : x->values[--l]; // must be a right-fold

  for (int i = l; i--;) {
    Args fargs{f, r, x->values[i]};
    r = f->call(2, fargs);
  }

  return r;
}

} // namespace cxbqn::rt_native::r0
