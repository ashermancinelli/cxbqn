#pragma once
#include <cxbqn/types.hpp>

/*
 * After the runtime has been initialized, we can replace parts of r0 and r1
 * with native functions. This header declares elements of r0 and r1 that CXBQN
 * replaces.
 */

namespace cxbqn::rt_native {

using namespace cxbqn::types;

// Perform replacesments in the driver
void replace_r0_with_native(O<Array> r0);
void replace_r1_with_native(O<Array> r1);

#define CXBQN_BUILTIN_DECL(PARENT, T, ...)                                     \
  struct T : public PARENT {                                                   \
    std::ostream &repr(std::ostream &os) const override {                      \
      return os << __VA_ARGS__;                                                \
    }                                                                          \
    O<Value> call(u8 nargs, Args &args) override;  \
  };

#define CXBQN_BUILTIN_FN_DECL(T, ...)                                          \
  CXBQN_BUILTIN_DECL(Function, T, __VA_ARGS__);

// Declarations of replacements
namespace r0 {

// ⌊ ⌈ | < > ≠ ≥ ⊢ ⊣ ∾ ⋈ ↑ ↓ ⊏ ˙ ˜ ¨ ´ ∘ ○ ⊸ ⟜ ◶ ⍟
CXBQN_BUILTIN_FN_DECL(Less, "<");
CXBQN_BUILTIN_FN_DECL(NE, "≠");
CXBQN_BUILTIN_FN_DECL(Rtack, "⊢");
CXBQN_BUILTIN_FN_DECL(Ltack, "⊣");
CXBQN_BUILTIN_FN_DECL(JoinTo, "∾");
CXBQN_BUILTIN_FN_DECL(EnlistPair, "⋈");
CXBQN_BUILTIN_FN_DECL(Take, "↑");
CXBQN_BUILTIN_FN_DECL(Drop, "↓");
CXBQN_BUILTIN_FN_DECL(Constant, "˙");
CXBQN_BUILTIN_DECL(Md1, SelfSwap, "˜");
CXBQN_BUILTIN_DECL(Md1, Each, "¨");
CXBQN_BUILTIN_DECL(Md1, Fold, "´");
CXBQN_BUILTIN_DECL(Md2, Atop, "∘");
CXBQN_BUILTIN_DECL(Md2, Over, "○");
CXBQN_BUILTIN_DECL(Md2, Before, "⊸");
CXBQN_BUILTIN_DECL(Md2, After, "⟜");
CXBQN_BUILTIN_DECL(Md2, Choose, "◶");
CXBQN_BUILTIN_DECL(Md2, Repeat, "⍟");

} // namespace r0

} // namespace cxbqn::rt_native
