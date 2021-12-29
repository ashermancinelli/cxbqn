#include <cxbqn/rt_native.hpp>
#include <sstream>

namespace cxbqn::rt_native::r0 {

O<Value> Fold::call(u8 nargs, Args &args) {
  const auto f = args[4];
  const auto x = dyncast<ArrayBase>(args[1]);
  const auto w = args[2];

  {
    auto const sh = x->shape;
    if (0 == sh.size())
      return CXBQN_NEW(Array);
  }

  auto l = x->shape[0];
  auto r = 2 == nargs ? w : x->get(--l); // must be a right-fold

  for (int i = l; i--;) {
    Args fargs{f, r, x->get(i)};
    r = f->call(2, fargs);
  }

  return r;
}

} // namespace cxbqn::rt_native::r0
