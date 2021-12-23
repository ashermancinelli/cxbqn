#include <cxbqn/rt_native.hpp>

namespace cxbqn::rt_native::r0 {

O<Value> Choose::call(u8 nargs, Args &args) {
  auto f = args[4];
  // 𝕨𝔽𝕩 gives index into 𝕘, so 𝕘 must be array
  auto g = dyncast<Array>(args[5]);

  auto x = args[1];
  auto w = args[2];

  Args choose_args{f, x, w};
  auto choseni = dyncast<Number>(f->call(nargs, choose_args))->v;

  auto ff = g->values[choseni];

  Args retargs{ff, x, w};
  return ff->call(nargs, retargs);
}

} // namespace cxbqn::rt_native::r0
