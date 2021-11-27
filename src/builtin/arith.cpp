#include "provides_helpers.hpp"

namespace cxbqn::provides {

// Shorthand to define the call method of a given builtin type.
// `ox` and `ow` are short for the opaque pointers to each argument, in case the
// operator needs to do some checks on the values before casting them.
#define CXBQN_BI_CALL_DEF_NUMONLY(TYPE, SYMBOL, RETURN)                        \
  O<Value> TYPE::call(u8 nargs, Args args) {                  \
    CXBQN_DEBUG(SYMBOL ":nargs={},args={}", nargs, args);                      \
    XNULLCHK(SYMBOL);                                                          \
    auto ox = args[1];                                                         \
    auto ow = args[2];                                                         \
    auto x = dyncast<Number>(args[1]);                       \
    auto w = dyncast<Number>(args[2]);                       \
    auto ret = (RETURN);                                                       \
    return ret;                                                                \
  }

CXBQN_BI_CALL_DEF_NUMONLY(Ceil, "⌈",
                          NN(2 == nargs ? std::max(w->v, x->v)
                                        : std::ceil(x->v)));
CXBQN_BI_CALL_DEF_NUMONLY(Not, "¬",
                          NN(2 == nargs ? 1 + (w->v - x->v) : 1 - x->v));
CXBQN_BI_CALL_DEF_NUMONLY(And, "∧", NN(w->v * x->v));
CXBQN_BI_CALL_DEF_NUMONLY(Or, "∨",
                          (2 == nargs ? NN((w->v + x->v) - (w->v * x->v))
                                      : args[1]));
CXBQN_BI_CALL_DEF_NUMONLY(LT, "<", NNC(w->v < x->v));
CXBQN_BI_CALL_DEF_NUMONLY(GT, ">", NNC(w->v > x->v));
CXBQN_BI_CALL_DEF_NUMONLY(NE, "≠", NNC(!feq_helper(x->v, w->v)));

CXBQN_BI_CALL_DEF_NUMONLY(GE, "≥", NNC(w->v > x->v || feq_helper(x->v, w->v)));
CXBQN_BI_CALL_DEF_NUMONLY(Ltack, "⊣", args[2]);
CXBQN_BI_CALL_DEF_NUMONLY(Rtack, "⊣", args[1]);

CXBQN_BI_CALL_DEF_NUMONLY(Fill, "Fill", 2 == nargs ? args[1] : NN(0));
CXBQN_BI_CALL_DEF_NUMONLY(Log, "Log",
                          2 == nargs ? NN(std::log(x->v) / std::log(w->v))
                                     : NN(std::log(x->v)));

} // namespace cxbqn::provides
