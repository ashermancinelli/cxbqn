#pragma once
#include <cxbqn/cxbqn.hpp>

namespace cxbqn::provides {

using namespace cxbqn::types;

/*
 * The runtime as needed by the the final compiler.
 *
 * The *_cached alternatives will save the runtime when it's first called, and
 * just return a copy on subsequent calls.
 */
O<Array> get_runtime_setprims();
O<Array> get_runtime_setprims_cached();

/*
 * The runtime as theoretically needed by the final compiler, without
 * `SetPrims Decompose‿PrimInd` having been called.
 */
O<Array> get_runtime();
O<Array> get_runtime_cached();

/*
 * The parts of the runtime given in the `provides` array, but in the positions
 * needed by the `runtime` array. This is useful for testing the input to
 * provides on bytecode tests generated from the `simple.bqn` or `prim.bqn`
 * tests.
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

#define CXBQN_BUILTIN_DECL(PARENT, T, ...)                                     \
  struct T : public PARENT {                                                   \
    std::ostream &repr(std::ostream &os) const override {                      \
      return os << __VA_ARGS__;                                                \
    }                                                                          \
    O<Value> call(u8 nargs = 0, std::vector<O<Value>> args = {}) override;     \
  };                                                                           \
  O<Value> bi_##T();

#define CXBQN_BUILTIN_FN_DECL(T, ...)                                          \
  CXBQN_BUILTIN_DECL(Function, T, __VA_ARGS__);

// Arithmatic
CXBQN_BUILTIN_FN_DECL(Plus, "+");
CXBQN_BUILTIN_FN_DECL(Minus, "-");
CXBQN_BUILTIN_FN_DECL(Mul, "×");
CXBQN_BUILTIN_FN_DECL(Div, "÷");
CXBQN_BUILTIN_FN_DECL(Power, "⋆");
CXBQN_BUILTIN_FN_DECL(Root, "√");
CXBQN_BUILTIN_FN_DECL(Floor, "⌊");
CXBQN_BUILTIN_FN_DECL(Ceil, "⌈");
CXBQN_BUILTIN_FN_DECL(Stile, "|");

// Bool
CXBQN_BUILTIN_FN_DECL(Not, "¬");
CXBQN_BUILTIN_FN_DECL(And, "∧");
CXBQN_BUILTIN_FN_DECL(Or, "∨");
CXBQN_BUILTIN_FN_DECL(LT, "<");
CXBQN_BUILTIN_FN_DECL(GT, ">");
CXBQN_BUILTIN_FN_DECL(NE, "≠");
CXBQN_BUILTIN_FN_DECL(EQ, "=");
CXBQN_BUILTIN_FN_DECL(LE, "≤");
CXBQN_BUILTIN_FN_DECL(GE, "≥");
CXBQN_BUILTIN_FN_DECL(FEQ, "≡");
CXBQN_BUILTIN_FN_DECL(FNE, "≢");

// Only some of these are needed to bootstrap the runtime
CXBQN_BUILTIN_FN_DECL(Ltack, "⊣");
CXBQN_BUILTIN_FN_DECL(Rtack, "⊢");
CXBQN_BUILTIN_FN_DECL(ArrayDepth, "≡");
CXBQN_BUILTIN_FN_DECL(Type, "•Type");
CXBQN_BUILTIN_FN_DECL(Fill, "•Fill");
CXBQN_BUILTIN_FN_DECL(Log, "Log");
CXBQN_BUILTIN_FN_DECL(Assert, "!");
CXBQN_BUILTIN_FN_DECL(Range, "↕");
CXBQN_BUILTIN_FN_DECL(Pick, "⊑");
CXBQN_BUILTIN_FN_DECL(Shape, "≢");
CXBQN_BUILTIN_FN_DECL(Deshape, "⥊");
CXBQN_BUILTIN_FN_DECL(GroupLen, "•GroupLen");
CXBQN_BUILTIN_FN_DECL(GroupOrd, "•GroupOrd");
CXBQN_BUILTIN_FN_DECL(FmtNum, "•FmtNum");

CXBQN_BUILTIN_DECL(Md1, Table, "⌜");
CXBQN_BUILTIN_DECL(Md1, Scan, "`");

CXBQN_BUILTIN_DECL(Md2, FillBy, "•_fillBy_");
CXBQN_BUILTIN_DECL(Md2, Valence, "⊘");
CXBQN_BUILTIN_DECL(Md2, Catch, "⎊");

struct Glyph : public Function {
  std::vector<O<Value>> runtime;
  Glyph(O<Value> _runtime)
      : runtime{dynamic_pointer_cast<Array>(_runtime)->values} {}
  O<Value> call(u8 nargs = 0, std::vector<O<Value>> args = {}) override;
  std::ostream &repr(std::ostream &os) const override { return os << "•Glyph"; }
};

struct Decompose : public Function {

  Decompose(O<Value> _runtime)
      : runtime{dynamic_pointer_cast<Array>(_runtime)->values} {}

  std::ostream &repr(std::ostream &os) const override {
    return os << "•Decompose";
  }

  // Decompose needs to check if a value is a primitive, so we store a view of
  // the runtime to check.
  std::vector<O<Value>> runtime;

  O<Value> call(u8 nargs = 0, std::vector<O<Value>> args = {}) override;
};
O<Value> bi_Decompose();

struct PrimInd : public Function {

  PrimInd(O<Value> _runtime)
      : runtime{dynamic_pointer_cast<Array>(_runtime)->values} {}

  std::ostream &repr(std::ostream &os) const override {
    return os << "PrimInd";
  }

  // PrimInd returns the index of a value in the runtime if it exists, so we
  // need to store the runtime in the object.
  std::vector<O<Value>> runtime;

  O<Value> call(u8 nargs = 0, std::vector<O<Value>> args = {}) override;
};
O<Value> bi_PrimInd();

} // namespace cxbqn::provides

namespace cxbqn::sys {

using namespace cxbqn::types;

// Simple system functions
CXBQN_BUILTIN_FN_DECL(CXBQN, "•CXBQN");
CXBQN_BUILTIN_FN_DECL(Show, "•Show");
CXBQN_BUILTIN_FN_DECL(Timed, "•_timed");
CXBQN_BUILTIN_FN_DECL(UnixTime, "•UnixTime");
CXBQN_BUILTIN_FN_DECL(FLines, "•FLines");
CXBQN_BUILTIN_FN_DECL(Exit, "•Exit");
CXBQN_BUILTIN_FN_DECL(List, "•List");

/* NONSTANDARD
 *
 * Run with: `•SH "ls"‿"-lah"‿"~"`, get back list `exitcode‿output`.
 * Note that stdout is merged with stdin.
 *
 * Optionally pass working directory as 𝕨.
 */
CXBQN_BUILTIN_FN_DECL(SH, "•SH");

// System functions that require pointers to objects we need at runtime, for
// example the runtime itself.
struct SystemFunctionResolver : public Function {

  SystemFunctionResolver(O<Array> args, O<Value> fmt, O<Value> repr,
                         O<Value> compiler, O<Array> runtime, O<Array> path)
      : _args{args}, _fmt{fmt}, _repr{repr}, _compiler{compiler},
        _runtime{runtime}, _path{path} {}

  std::ostream &repr(std::ostream &os) const override {
    return os << "•SystemFunctionResolver";
  }

  O<Array> _args;
  O<Array> _path;
  O<Value> _fmt;
  O<Value> _repr;
  O<Value> _compiler;
  O<Array> _runtime;

  O<Value> call(u8 nargs = 0, std::vector<O<Value>> args = {}) override;
};

struct CUDAFor : public Function {
  CUDAFor(O<Array> runtime) : _runtime{runtime} {}
  O<Array> _runtime;
};

struct BQN : public Function {

  BQN(O<Value> compiler, O<Array> compiler_args)
      : _compiler{compiler}, _compiler_args{compiler_args} {}

  std::ostream &repr(std::ostream &os) const override {
    return os << "•Import";
  }

  O<Value> _compiler;
  O<Array> _compiler_args;

  O<Value> call(u8 nargs = 0, std::vector<O<Value>> args = {}) override;
};

struct Import : public Function {

  Import(O<Value> compiler, O<Array> compiler_args)
      : _compiler{compiler}, _compiler_args{compiler_args} {}

  std::ostream &repr(std::ostream &os) const override {
    return os << "•Import";
  }

  O<Value> _compiler;
  O<Array> _compiler_args;

  O<Value> call(u8 nargs = 0, std::vector<O<Value>> args = {}) override;
};

struct Out : public Function {

  Out(O<Value> fmt) : _fmt{fmt} {}

  std::ostream &repr(std::ostream &os) const override {
    return os << "•Out";
  }

  O<Value> _fmt;

  O<Value> call(u8 nargs = 0, std::vector<O<Value>> args = {}) override;
};

} // namespace cxbqn::sys

#undef CXBQN_BUILTIN_DECL
