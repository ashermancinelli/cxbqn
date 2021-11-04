#include <cmath>
#include <cxbqn/debug.hpp>
#include <cxbqn/provides.hpp>

namespace cxbqn::provides {

namespace {

// The t() method on all values in cxbqn uses higher bits to indicate internal
// type annotations. We only want the lowest 3 bits for the builtin •Type.
static inline auto type_builtin(const Value *v) {
  return (v->t() & TypeType{0b111}).to_ulong();
}

// When we "reshape" an array, we just allocate enough memory to hold all the
// elements and assign the shape feild to be the shape we expect.
static inline void reshape(Array *arr, std::initializer_list<uz> shape) {
  const auto n =
      std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<uz>());
  arr->N = n;
  arr->values.resize(n);
}

// Recursively find the max depth of each element, and max reduce
static uz array_depth_helper(uz init, Value *v) {
  CXBQN_DEBUG("array_depth_helper:init={},value={}", init, CXBQN_STR_NC(v));
  if (t_Array == type_builtin(v)) {
    auto *ar = dynamic_cast<Array *>(v);
    return init +
           std::accumulate(ar->values.begin(), ar->values.end(), 1,
                           [](uz acc, auto b) {
                             return std::max(acc, array_depth_helper(0, b));
                           });
  } else
    return 1 + init;
}

// For floating point comparisons, we use 10 times the machine precision.
// Subject to change.
static bool feq_helper(f64 a, f64 b) {
  return std::abs(a - b) < (10 * std::numeric_limits<f64>::epsilon());
}

} // namespace

// I promise this makes the definitions more readable :)
#define NN(x) new Number(x)

// "new number casted", creates a new number after casting some expression into
// an f64
#define NNC(x) new Number(static_cast<f64>(x))

// Shorthand to define the call method of a given builtin type
#define CXBQN_BI_CALL_DEF_NUMONLY(TYPE, SYMBOL, PREAMBLE, RETURN)              \
  Value *TYPE::call(u8 nargs, std::vector<Value *> args) {                     \
    CXBQN_DEBUG(SYMBOL ":nargs={},args={}", nargs, args);                      \
    auto *x = dynamic_cast<Number *>(args[1]);                                 \
    auto *w = dynamic_cast<Number *>(args[2]);                                 \
    PREAMBLE;                                                                  \
    return (RETURN);                                                           \
  }

CXBQN_BI_CALL_DEF_NUMONLY(Plus, "+", {},
                          1 == nargs ? args[1] : NN(x->v + w->v));
CXBQN_BI_CALL_DEF_NUMONLY(Minus, "-", {}, NN(2 == nargs ? w->v - x->v : -x->v));
Value *Mul::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG("×:nargs={},args={}", nargs, args);
  auto *x = dynamic_cast<Number *>(args[1]);
  auto *w = dynamic_cast<Number *>(args[2]);
  if (2 == nargs)
    return NN(w->v * x->v);
  return NN(feq_helper(0.0, x->v) ? 0 : x->v > 0 ? 1 : 0);
}
CXBQN_BI_CALL_DEF_NUMONLY(Div, "÷", {},
                          NN(2 == nargs ? w->v / x->v : 1 / x->v));
CXBQN_BI_CALL_DEF_NUMONLY(Power, "×", {},
                          NN(2 == nargs ? std::pow(w->v, x->v)
                                        : std::exp(x->v)));
CXBQN_BI_CALL_DEF_NUMONLY(Root, "√", {},
                          NN(2 == nargs ? std::pow(x->v, 1 / w->v)
                                        : std::sqrt(x->v)));

CXBQN_BI_CALL_DEF_NUMONLY(Floor, "⌊", {},
                          NN(2 == nargs ? std::min(w->v, x->v)
                                        : std::floor(x->v)));
CXBQN_BI_CALL_DEF_NUMONLY(Ceil, "⌈", {},
                          NN(2 == nargs ? std::max(w->v, x->v)
                                        : std::ceil(x->v)));
CXBQN_BI_CALL_DEF_NUMONLY(Stile, "|", {},
                          NN(2 == nargs ? std::fmod(w->v, x->v)
                                        : std::abs(x->v)));
CXBQN_BI_CALL_DEF_NUMONLY(Not, "¬", {},
                          NN(2 == nargs ? 1 + (w->v - x->v) : 1 - x->v));
CXBQN_BI_CALL_DEF_NUMONLY(And, "∧", {}, NN(w->v * x->v));
CXBQN_BI_CALL_DEF_NUMONLY(Or, "∨", {},
                          (2 == nargs ? NN((w->v + x->v) - (w->v * x->v))
                                      : args[1]));
CXBQN_BI_CALL_DEF_NUMONLY(LT, "<", {}, NNC(w->v < x->v));
CXBQN_BI_CALL_DEF_NUMONLY(GT, ">", {}, NNC(w->v > x->v));
CXBQN_BI_CALL_DEF_NUMONLY(NE, "≠", {}, NNC(!feq_helper(x->v, w->v)));
CXBQN_BI_CALL_DEF_NUMONLY(EQ, "=", {}, NNC(feq_helper(x->v, w->v)));
CXBQN_BI_CALL_DEF_NUMONLY(LE, "≤", {}, NNC(w->v < x->v || feq_helper(x->v, w->v)));
CXBQN_BI_CALL_DEF_NUMONLY(GE, "≥", {}, NNC(w->v > x->v || feq_helper(x->v, w->v)));
CXBQN_BI_CALL_DEF_NUMONLY(FEQ, "feq", {}, NNC(feq_helper(x->v, w->v)));
CXBQN_BI_CALL_DEF_NUMONLY(FNE, "fne", {}, NNC(!feq_helper(x->v, w->v)));
CXBQN_BI_CALL_DEF_NUMONLY(Ltack, "⊣", {}, args[2]);
CXBQN_BI_CALL_DEF_NUMONLY(Rtack, "⊣", {}, args[1]);
CXBQN_BI_CALL_DEF_NUMONLY(Type, "•Type", {}, NNC(type_builtin(args[1])));

Value *Table::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG("⌜: nargs={},args={}", nargs, args);
  if (1 == nargs)
    throw std::runtime_error("⌜: no monadic definition");
  if (0 != type_builtin(args[1]))
    throw std::runtime_error("⌜: 𝕩 must be an array");
  if (0 != type_builtin(args[2]))
    throw std::runtime_error("⌜: 𝕨 must be an array");
  auto *x = dynamic_cast<Array *>(args[1]);
  auto *w = dynamic_cast<Array *>(args[2]);
  auto *ret = new Array(x->N * w->N);
  CXBQN_DEBUG("⌜:create return array with size={}", ret->N);
  for (int i = 0; i < x->N; i++)
    for (int j = 0; j < w->N; j++)
      ret->values[(i * x->N) + w->N] =
          args[0]->call(2, {args[0], x->values[i], w->values[j]});

  CXBQN_DEBUG("⌜:assigned all values. setting shape of return value.");

  // The return value has shape {shape w destructured, shape x destructured},
  // so we will copy the contents of the shape of w to the return value's shape,
  // and then extend with the shape of x.
  ret->shape.clear();
  std::copy(w->shape.begin(), w->shape.end(), std::back_inserter(ret->shape));
  std::copy(x->shape.begin(), x->shape.end(), std::back_inserter(ret->shape));
  return ret;
}

Value *ArrayDepth::call(u8 nargs, std::vector<Value *> args) {
  return new Number(static_cast<f64>(array_depth_helper(0, args[1])));
}

// Value *Type::call(u8 nargs, std::vector<Value *> args) { }

} // namespace cxbqn::provides
