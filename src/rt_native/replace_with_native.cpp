#include <cxbqn/rt_native.hpp>

namespace cxbqn::rt_native {

using namespace cxbqn;
using namespace cxbqn::types;

// ⌊ ⌈ | < > ≠ ≥ ⊢ ⊣ ∾ ⋈ ↑ ↓ ⊏ ˙ ˜ ¨ ´ ∘ ○ ⊸ ⟜ ◶ ⍟
void replace_r0_with_native(O<Array> r0) {
  //r0->values[16] = CXBQN_NEW(r0::Each);       // ¨
#ifdef CXBQN_NATIVE_R0
  r0->values[3] = CXBQN_NEW(r0::Less);        // <
  r0->values[5] = CXBQN_NEW(r0::NE);          // ≠
  r0->values[7] = CXBQN_NEW(r0::Rtack);       // ⊢
  r0->values[8] = CXBQN_NEW(r0::Ltack);       // ⊣
  r0->values[9] = CXBQN_NEW(r0::JoinTo);      // ∾
  r0->values[10] = CXBQN_NEW(r0::EnlistPair); // ⋈
  r0->values[11] = CXBQN_NEW(r0::Take);       // ↑
  r0->values[12] = CXBQN_NEW(r0::Drop);       // ↓
  r0->values[13] = CXBQN_NEW(r0::Select);     // ⊏
  r0->values[14] = CXBQN_NEW(r0::Constant);   // ˙
  r0->values[15] = CXBQN_NEW(r0::SelfSwap);   // ˜
  r0->values[17] = CXBQN_NEW(r0::Fold);       // ´
  r0->values[18] = CXBQN_NEW(r0::Atop);       // ∘
  r0->values[19] = CXBQN_NEW(r0::Over);       // ○
  r0->values[20] = CXBQN_NEW(r0::Before);     // ⊸
  r0->values[21] = CXBQN_NEW(r0::After);      // ⟜
  r0->values[22] = CXBQN_NEW(r0::Choose);     // ◶
  r0->values[23] = CXBQN_NEW(r0::Repeat);     // ⍟
#else
#warning                                                                       \
    "you probably don't want BQN-only r0. enable CXBQN_NATIVE_R0 to avoid this warning."
#endif
}

void replace_r1_with_native(O<Array> r1) {}

} // namespace cxbqn::rt_native
