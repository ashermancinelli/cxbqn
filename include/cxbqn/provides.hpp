#pragma once
#include <cxbqn/cxbqn.hpp>

namespace cxbqn::provides {

using namespace cxbqn::types;

struct Provides : public Function {
  virtual TypeType t() const {
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

CXBQN_BUILTIN_DECL(Plus, "+");
CXBQN_BUILTIN_DECL(Minus, "-");
CXBQN_BUILTIN_DECL(Mul, "×");
CXBQN_BUILTIN_DECL(Div, "÷");
CXBQN_BUILTIN_DECL(Power, "⋆");
CXBQN_BUILTIN_DECL(Root, "√");
CXBQN_BUILTIN_DECL(Floor, "⌊");
CXBQN_BUILTIN_DECL(Ceil, "⌈");
//
CXBQN_BUILTIN_DECL(FEQ, "feq");
CXBQN_BUILTIN_DECL(FNE, "fne");
CXBQN_BUILTIN_DECL(ArrayDepth, "≡");
CXBQN_BUILTIN_DECL(Type, "•Type");
CXBQN_BUILTIN_DECL(Table, "⌜");
/*
 * 0 bi_add
 * 1 bi_sub
 * 2 bi_mul
 * 3 bi_div
 * 4 bi_pow
 * 5 bi_root
 * 6 bi_floor
 * 7 bi_ceil
 * 8 bi_stile
 * 9 bi_not
 * 10 bi_and
 * 11 bi_or
 * 12 bi_lt
 * 13 bi_gt
 * 14 bi_ne
 * 15 bi_eq
 * 16 bi_le
 * 17 bi_ge
 * 18 bi_feq
 * 19 bi_fne
 * 20 bi_ltack
 * 21 bi_rtack
 * 22 bi_shape
 * 23 bi_join
 * 24 bi_couple
 * 25 bi_pair
 * 26 bi_take
 * 27 bi_drop
 */

#undef CXBQN_BUILTIN_DECL

Array *get_runtime();
Value* bi_plus();
Value* bi_minus();
Value* bi_mul();
Value* bi_div();
Value* bi_power();
Value* bi_root();
Value* bi_floor();
Value* bi_ceil();
Value* bi_feq();
Value* bi_fne();
Value* bi_arraydepth();
Value* bi_type();
Value* bi_table();

} // namespace cxbqn::provides
