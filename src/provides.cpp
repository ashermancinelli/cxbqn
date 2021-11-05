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

#define CHR_MAX 1114111
static inline Value *check_char(Value *v) {
  if (t_Character != type_builtin(v))
    throw std::runtime_error("internal: invalid value passed to check_char");
  auto f = dynamic_cast<Character *>(v)->v;
  if (f < 0 || f > CHR_MAX)
    throw std::runtime_error("invalid code point");
  return v;
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
template <typename T = f64> static bool feq_helper(T a, T b) {
#define INF std::numeric_limits<T>::infinity()
  if (a == INF and b == INF)
    return true;
  if (a == -INF and b == -INF)
    return true;
#undef INF
  return std::abs(a - b) < (10 * std::numeric_limits<T>::epsilon());
}

} // namespace

// I promise this makes the definitions more readable :)
#define NN(x) new Number(x)

// "new number casted", creates a new number after casting some expression into
// an f64
#define NNC(x) new Number(static_cast<f64>(x))

// Shorthand to define the call method of a given builtin type.
// `ox` and `ow` are short for the opaque pointers to each argument, in case the
// operator needs to do some checks on the values before casting them.
#define CXBQN_BI_CALL_DEF_NUMONLY(TYPE, SYMBOL, PREAMBLE, RETURN)              \
  Value *TYPE::call(u8 nargs, std::vector<Value *> args) {                     \
    CXBQN_DEBUG(SYMBOL ":nargs={},args={}", nargs, args);                      \
    auto *ox = args[1];                                                        \
    auto *ow = args[2];                                                        \
    auto *x = dynamic_cast<Number *>(args[1]);                                 \
    auto *w = dynamic_cast<Number *>(args[2]);                                 \
    PREAMBLE;                                                                  \
    auto *ret = (RETURN);                                                      \
    return ret;                                                                \
  }

Value *Plus::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG("+:nargs={},args={}", nargs, args);
  auto *ox = args[1];
  auto *ow = args[2];
  auto *x = dynamic_cast<Number *>(args[1]);
  auto *w = dynamic_cast<Number *>(args[2]);
  if (t_Character == type_builtin(ox) and t_Character == type_builtin(ow))
    throw std::runtime_error("+: Cannot add two characters");
  if (!ox->t()[t_DataValue] or !ow->t()[t_DataValue])
    throw std::runtime_error("+: Cannot add non-data values");
  if (t_Character == type_builtin(ox) || t_Character == type_builtin(ow)) {
    return check_char(new Character(x->v + w->v));
  }
  return NN(x->v + w->v);
}

CXBQN_BI_CALL_DEF_NUMONLY(
    Minus, "-",
    {
      if (t_Character == type_builtin(ow) and t_Number == type_builtin(ox)) {
        return check_char(new Character(w->v - x->v));
      }
      if (t_Character == type_builtin(ow) and t_Character == type_builtin(ox)) {
        return NN(w->v - x->v);
      }
      if (t_Number != type_builtin(ox))
        throw std::runtime_error("-: can only negate numbers");
    },
    NN(2 == nargs ? w->v - x->v : -x->v));
CXBQN_BI_CALL_DEF_NUMONLY(
    Mul, "×",
    {
      if (t_Number != type_builtin(ox) || t_Number != type_builtin(ow))
        throw std::runtime_error("×: arguments must be numbers");
      if (2 == nargs)
        return NN(w->v * x->v);
    },
    NN(feq_helper(0.0, x->v) ? 0
       : x->v > 0            ? 1
                             : 0));
CXBQN_BI_CALL_DEF_NUMONLY(Div, "÷", {},
                          NN(2 == nargs ? w->v / x->v : 1 / x->v));
CXBQN_BI_CALL_DEF_NUMONLY(Power, "⋆", {},
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
CXBQN_BI_CALL_DEF_NUMONLY(LE, "≤", {},
                          NNC(w->v < x->v || feq_helper(x->v, w->v)));
CXBQN_BI_CALL_DEF_NUMONLY(GE, "≥", {},
                          NNC(w->v > x->v || feq_helper(x->v, w->v)));
CXBQN_BI_CALL_DEF_NUMONLY(FEQ, "≡", {}, NNC(feq_helper(x->v, w->v)));
CXBQN_BI_CALL_DEF_NUMONLY(FNE, "≢", {}, NNC(!feq_helper(x->v, w->v)));
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

CXBQN_BI_CALL_DEF_NUMONLY(Fill, "Fill", {}, 2 == nargs ? args[1] : NN(0));
CXBQN_BI_CALL_DEF_NUMONLY(Log, "Log", {},
                          2 == nargs ? NN(std::log(w->v) / std::log(x->v))
                                     : NN(std::log(x->v)));
Value *Assert::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG("!: nargs={},args={}", nargs, args);
  bool shoulddie = false;
  if (t_Number != type_builtin(args[1]))
    shoulddie = true;
  if (!feq_helper(1., dynamic_cast<Number *>(args[1])->v))
    shoulddie = true;
  if (shoulddie) {
    CXBQN_CRIT("{} ! {}", (2 == nargs ? CXBQN_STR_NC(args[2]) : ""),
               CXBQN_STR_NC(args[1]));
    throw std::runtime_error("!");
  }
  return args[1];
}

Value *Range::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG("↕: nargs={},args={}", nargs, args);
  auto n = static_cast<uz>(dynamic_cast<Number *>(args[1])->v);
  auto *arr = new Array(n);
  std::iota(arr->values.begin(), arr->values.end(), 0);
  return arr;
}

Value *Pick::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG("⊑: nargs={},args={}", nargs, args);
  auto n = static_cast<uz>(dynamic_cast<Number *>(args[2])->v);
  return dynamic_cast<Array *>(args[1])->values[n];
}

CXBQN_BI_CALL_DEF_NUMONLY(
    Shape, "≢",
    {
      auto *ret = new Array();
      auto sh = dynamic_cast<Array *>(args[1])->shape;
      ret->values.assign(sh.begin(), sh.end());
    },
    ret);

Value *Deshape::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG("⥊: nargs={},args={}", nargs, args);
  auto *ret = new Array();
  auto *ar = dynamic_cast<Array *>(args[1]);
  ret->shape.assign({ar->N});
  std::copy(ar->values.begin(), ar->values.end(), ret->values.begin());
  return ret;
}

/* see these docs https://mlochbaum.github.io/BQN/doc/scan.html
 * you'll use more 𝕨, 𝕩 and 𝕗 from args, so probs do some length checking on
 * args before you try to grab the modified function from there */
Value *Scan::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG("`: nargs={},args={}", nargs, args);
  return nullptr;
  //auto *rhs = dynamic_cast<Array *>(args[1]);
  //auto *ret = new Array(rhs->N);
  //Value *acc;
  //ret->values[0] = acc = lhs->call(2, rhs->values[0], rhs->values[1]);
  //for (int i = 2; i < rhs->N; i++) {
  //  ret->values[i - 1] = lhs->call(2, rhs->values[i], rhs->values[i - 1]);
  //}
  //return ret;
}

} // namespace cxbqn::provides
