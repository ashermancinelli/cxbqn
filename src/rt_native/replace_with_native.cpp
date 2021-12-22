#include <cxbqn/rt_native.hpp>

namespace cxbqn::rt_native {

using namespace cxbqn;
using namespace cxbqn::types;

// ⌊ ⌈ | < > ≠ ≥ ⊢ ⊣ ∾ ⋈ ↑ ↓ ⊏ ˙ ˜ ¨ ´ ∘ ○ ⊸ ⟜ ◶ ⍟
void replace_r0_with_native(O<Array> r0) {
  r0->values[5] = CXBQN_NEW(r0::NE);          // ≠
  r0->values[7] = CXBQN_NEW(r0::Rtack);       // ⊢
  r0->values[8] = CXBQN_NEW(r0::Ltack);       // ⊣
  r0->values[9] = CXBQN_NEW(r0::JoinTo);      // ∾
  r0->values[10] = CXBQN_NEW(r0::EnlistPair); // ⋈
  r0->values[11] = CXBQN_NEW(r0::Take);       // ↑
  r0->values[12] = CXBQN_NEW(r0::Drop);       // ↓
  r0->values[15] = CXBQN_NEW(r0::SelfSwap);   // ˜
  r0->values[16] = CXBQN_NEW(r0::Each);       // ¨
}

void replace_r1_with_native(O<Array> r1) {}

} // namespace cxbqn::rt_native
