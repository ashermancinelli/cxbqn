#pragma once
#include <cxbqn/cxbqn.hpp>

namespace cxbqn::provides {

using namespace cxbqn::types;

/*
 * The runtime as needed by the the final compiler
 */
Array *get_runtime();

/* 
 * The core runtime as specified at [this link](https://mlochbaum.github.io/BQN/implementation/vm.html#runtime).
 * This is used to bootstrap the self-hosted runtime and compiler.
 */
Array *get_provides();

struct Provides : public Function {
  TypeType t() const override {
    return TypeType{t_Function | annot(t_Primitive)};
  }
};

#define CXBQN_BUILTIN_DECL(T, ...)                                             \
  struct T : public Provides {                                                 \
    std::ostream &repr(std::ostream &os) const override {                      \
      return os << __VA_ARGS__;                                                \
    }                                                                          \
    Value *call(u8 nargs = 0, std::vector<Value *> args = {}) override;        \
  };

// Arithmatic
CXBQN_BUILTIN_DECL(Plus, "+");
CXBQN_BUILTIN_DECL(Minus, "-");
CXBQN_BUILTIN_DECL(Mul, "×");
CXBQN_BUILTIN_DECL(Div, "÷");
CXBQN_BUILTIN_DECL(Power, "⋆");
CXBQN_BUILTIN_DECL(Root, "√");
CXBQN_BUILTIN_DECL(Floor, "⌊");
CXBQN_BUILTIN_DECL(Ceil, "⌈");
CXBQN_BUILTIN_DECL(Stile, "|");
Value* bi_plus();
Value* bi_minus();
Value* bi_mul();
Value* bi_div();
Value* bi_power();
Value* bi_root();
Value* bi_floor();
Value* bi_ceil();
Value* bi_stile();

// Bool
CXBQN_BUILTIN_DECL(Not, "¬");
CXBQN_BUILTIN_DECL(And, "∧");
CXBQN_BUILTIN_DECL(Or, "∨");
CXBQN_BUILTIN_DECL(LT, "<");
CXBQN_BUILTIN_DECL(GT, ">");
CXBQN_BUILTIN_DECL(NE, "≠");
CXBQN_BUILTIN_DECL(EQ, "=");
CXBQN_BUILTIN_DECL(LE, "≤");
CXBQN_BUILTIN_DECL(GE, "≥");
CXBQN_BUILTIN_DECL(FEQ, "≡");
CXBQN_BUILTIN_DECL(FNE, "≢");
Value* bi_not();
Value* bi_and();
Value* bi_or();
Value* bi_lt();
Value* bi_gt();
Value* bi_ne();
Value* bi_eq();
Value* bi_le();
Value* bi_ge();
Value* bi_feq();
Value* bi_fne();

// Only some of these are needed to bootstrap the runtime
CXBQN_BUILTIN_DECL(Ltack, "⊣");
CXBQN_BUILTIN_DECL(Rtack, "⊢");
CXBQN_BUILTIN_DECL(ArrayDepth, "≡");
CXBQN_BUILTIN_DECL(Type, "•Type");
CXBQN_BUILTIN_DECL(Table, "⌜");
CXBQN_BUILTIN_DECL(Fill, "Fill");
CXBQN_BUILTIN_DECL(Log, "Log");
CXBQN_BUILTIN_DECL(Assert, "!");
Value* bi_ltack();
Value* bi_rtack();
Value* bi_arraydepth();
Value* bi_type();
Value* bi_table();
Value* bi_fill();
Value* bi_log();
Value* bi_assert();

#undef CXBQN_BUILTIN_DECL

} // namespace cxbqn::provides
