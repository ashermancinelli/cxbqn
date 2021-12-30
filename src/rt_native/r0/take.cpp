#include <cxbqn/rt_native.hpp>
#include <cxbqn/array_utils.hpp>

namespace cxbqn::rt_native::r0 {

O<Value> Take::call(u8 nargs, Args &args) {
  auto x = dyncast<ArrayBase>(args[1]);
  auto xv = values(x);
  auto w = dyncast<Number>(args[2]);
  const auto l = static_cast<uz>(w->v);

  std::vector<O<Value>> vs(xv.begin(), xv.begin() + l);
  return CXBQN_NEW(Array, vs, {l});
}

} // namespace cxbqn::rt_native::r0
