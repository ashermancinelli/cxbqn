#pragma once
#include <cxbqn/cxbqn.hpp>

namespace cxbqn::provides {

using namespace cxbqn::types;

/*
 * The runtime as needed by the the final compiler
 */
O<Array> get_runtime();

/*
 * The parts of the runtime given in the `provides` array, but in the positions
 * needed by the `runtime` array. This is useful for testing the input to
 * provides on bytecode tests generated from the `simple.bqn` or `prim.bqn`
 * tests.
 *
 */
O<Array> get_runtime_bionly();

/*
 * The core runtime as specified at [this
 * link](https://mlochbaum.github.io/BQN/implementation/vm.html#runtime). This
 * is used to bootstrap the self-hosted runtime and compiler.
 */
O<Array> get_provides();

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
    O<Value> call(u8 nargs = 0, std::vector<O<Value>> args = {}) override;     \
  };                                                                           \
  O<Value> bi_##T();

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

// Only some of these are needed to bootstrap the runtime
CXBQN_BUILTIN_DECL(Ltack, "⊣");
CXBQN_BUILTIN_DECL(Rtack, "⊢");
CXBQN_BUILTIN_DECL(ArrayDepth, "≡");
CXBQN_BUILTIN_DECL(Type, "•Type");
CXBQN_BUILTIN_DECL(Table, "⌜");
CXBQN_BUILTIN_DECL(Fill, "Fill");
CXBQN_BUILTIN_DECL(Log, "Log");
CXBQN_BUILTIN_DECL(Assert, "!");
CXBQN_BUILTIN_DECL(Range, "↕");
CXBQN_BUILTIN_DECL(Pick, "⊑");
CXBQN_BUILTIN_DECL(Shape, "≢");
CXBQN_BUILTIN_DECL(Deshape, "⥊");
CXBQN_BUILTIN_DECL(Scan, "`");
CXBQN_BUILTIN_DECL(GroupLen, "GroupLen");
CXBQN_BUILTIN_DECL(GroupOrd, "GroupOrd");
CXBQN_BUILTIN_DECL(FillBy, "_fillBy_");
CXBQN_BUILTIN_DECL(Valence, "⊘");
CXBQN_BUILTIN_DECL(Catch, "⎊");

#undef CXBQN_BUILTIN_DECL

} // namespace cxbqn::provides
