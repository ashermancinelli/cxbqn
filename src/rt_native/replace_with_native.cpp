#include <cxbqn/rt_native.hpp>

namespace cxbqn::rt_native {

using namespace cxbqn;
using namespace cxbqn::types;

void replace_r0_with_native(O<Array> r0) {
  r0->values[15] = CXBQN_NEW(r0::SelfSwap); // ˜
}

void replace_r1_with_native(O<Array> r1) {}

} // namespace cxbqn::rt_native
