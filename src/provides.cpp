#include <cmath>
#include <cxbqn/debug.hpp>
#include <cxbqn/fmt.hpp>
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

template<typename T = f64> static bool fge_helper(T a, T b) {
  return feq_helper(a, b) or a > b;
}

template<typename T = f64> static bool fle_helper(T a, T b) {
  return feq_helper(a, b) or a < b;
}

} // namespace

// I promise this makes the definitions more readable :)
#define NN(x) new Number(x)

// "new number casted", creates a new number after casting some expression into
// an f64
#define NNC(x) new Number(static_cast<f64>(x))

// "dynamic cast to a number"
#define DCN(x) dynamic_cast<Number *>(x)

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
    NN(feq_helper(0.0, x->v) ? 0 : x->v > 0 ? 1 : 0));
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
CXBQN_BI_CALL_DEF_NUMONLY(
    EQ, "=",
    {
      if (1 == nargs)
        return args[1];
    },
    NNC(feq_helper(x->v, w->v)));
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
  auto *F = args[4];
  if (0 != type_builtin(args[1]) or 0 != type_builtin(args[2]))
    throw std::runtime_error("⌜: 𝕩 and 𝕨 must be arrays");

  auto *x = dynamic_cast<Array *>(args[1]);
  const auto &xv = x->values;
  auto *w = dynamic_cast<Array *>(args[2]);
  const auto &wv = w->values;
  auto *ret = new Array(x->N() * w->N());
  for (int iw = 0; iw < w->N(); iw++)
    for (int ix = 0; ix < x->N(); ix++) {
      ret->values[(iw * x->N()) + ix] = F->call(2, {F, xv[ix], wv[iw]});
    }
  ret->shape.assign(w->shape.begin(), w->shape.end());
  ret->shape.insert(ret->shape.end(), x->shape.begin(), x->shape.end());
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
  for (int i = 0; i < arr->N(); i++)
    arr->values[i] = new Number(i);
  return arr;
}

Value *Pick::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG("⊑: nargs={},args={}", nargs, args);
  auto n = static_cast<uz>(dynamic_cast<Number *>(args[2])->v);
  return dynamic_cast<Array *>(args[1])->values[n];
}

Value *Shape::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG("≢: nargs={},args={}", nargs, args);
  auto *ret = new Array();
  auto sh = dynamic_cast<Array *>(args[1])->shape;
  ret->values.resize(sh.size());
  for (int i = 0; i < sh.size(); i++)
    ret->values[i] = new Number(sh[i]);
  return ret;
}

Value *Deshape::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG("⥊: nargs={},args={}", nargs, args);

  const bool iswarr = t_Array == type_builtin(args[2]);
  const bool isxarr = t_Array == type_builtin(args[1]);
  auto *xarr = isxarr ? dynamic_cast<Array *>(args[1]) : nullptr;

  if (1 == nargs) {
    if (isxarr) {
      xarr->shape.assign({xarr->N()});
      return xarr;
    } else {
      return new Array({args[1]});
    }
  }

  auto *ret = new Array();
  if (iswarr) {
    auto *warr = dynamic_cast<Array *>(args[2]);
    for (int i = 0; i < warr->N(); i++)
      ret->shape.push_back(
          static_cast<uz>(dynamic_cast<Number *>(warr->values[i])->v));
  } else {
    ret->shape.push_back(static_cast<uz>(dynamic_cast<Number *>(args[2])->v));
  }

  const auto cnt = std::accumulate(ret->shape.begin(), ret->shape.end(), 1,
                                   std::multiplies<uz>());
  ret->values.resize(cnt);

  if (!isxarr)
    for (int i = 0; i < cnt; i++)
      ret->values[i] = args[1];
  else
    for (int i = 0; i < cnt; i++)
      ret->values[i] =
          xarr->values[i %
                       xarr->N()]; // values wrap when 𝕩 has insufficient length
  return ret;
}

Value *Scan::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG("`: nargs={},args={}", nargs, args);
  if (t_Array != type_builtin(args[1]))
    throw std::runtime_error("`: 𝕩 must have rank at least 1");

  auto *x = dynamic_cast<Array *>(args[1]);
  auto *w = args[2];
  auto *F = args[4];

  auto sh = x->shape;
  auto iswarr = (t_Array == type_builtin(w));
  if (2 == nargs) {
    auto w_rank = iswarr ? dynamic_cast<Array *>(w)->shape.size() : 0;
    if (1 + w_rank != x->shape.size())
      throw std::runtime_error("`: rank of 𝕨 must be cell rank of 𝕩");
    if (iswarr) {
      const auto &wsh = dynamic_cast<Array *>(w)->shape;
      for (int i = 0; i < x->shape.size() - 1; i++)
        if (wsh[i] != x->shape[i + 1])
          throw std::runtime_error("`: shape of 𝕨 must be cell shape of 𝕩");
    }
  }

  auto *ret = new Array();
  ret->values.resize(x->N());
  ret->shape.resize(x->shape.size());
  std::copy(x->shape.begin(), x->shape.end(), ret->shape.begin());

  // product reduction of shape of cells of 𝕩
  // const auto cnt = std::accumulate(x->shape.begin() + 1, x->shape.end(), 1,
  // std::multiplies<uz>());
  int cnt = 1;
  for (int i = 1; i < x->shape.size(); i++)
    cnt *= x->shape[i];
  int i = 0;
  auto *warr = iswarr ? dynamic_cast<Array *>(w) : new Array({w});
  CXBQN_DEBUG("cnt={},warr={}", cnt, CXBQN_STR_NC((Value *)warr));
  if (1 == nargs)
    for (; i < cnt; i++)
      ret->values[i] = x->values[i];
  else
    for (; i < cnt; i++) {
      auto *xv = x->values[i];
      auto *wv = warr->values[i];
      CXBQN_DEBUG("xv={},wv={},i={}", CXBQN_STR_NC(xv), CXBQN_STR_NC(wv), i);
      ret->values[i] = F->call(2, {F, x->values[i], warr->values[i]});
    }

  for (; i < x->N(); i++)
    ret->values[i] = F->call(2, {F, x->values[i], ret->values[i - cnt]});
  return ret;
}

/*
 * let group_len = (x,w) => { // ≠¨⊔ for a valid list argument
 *   let l=x.reduce((a,b)=>Math.max(a,b),(w||0)-1);
 *   let r=Array(l+1).fill(0);
 *   x.map(e=>{if(e>=0)r[e]+=1;});
 *   return list(r,0);
 * }
 */
#define SYMBOL "≠¨⊔𝕩"
Value *GroupLen::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG(SYMBOL ": nargs={},args={}", nargs, args);
  auto *x = dynamic_cast<Array *>(args[1]);
  auto *w = dynamic_cast<Number *>(args[2]); // only use if nargs == 2!
  const auto init = (2 == nargs ? w->v : 0) - 1;
  std::vector<f64> xs(x->N(), 0);
  for (int i = 0; i < x->N(); i++)
    xs[i] = DCN(x->values[i])->v;
  const auto l = std::accumulate(xs.begin(), xs.end(), init,
                                 [](auto a, auto b) { return std::max(a, b); });
  std::vector<f64> retv(static_cast<uz>(l+1), 0);
  std::fill(retv.begin(), retv.end(), 0);
  for (auto e : xs)
    if (fge_helper(e, 0.0))
      retv[static_cast<uz>(e)]++;
  auto *ret = new Array(retv.size());
  for (int i=0; i < ret->N(); i++)
    ret->values[i] = NN(retv[i]);
  return ret;
}
#undef SYMBOL

/*
 * let group_ord = (x,w) => { // ∾⊔x assuming w=group_len(x)
 *   let l=0,s=w.map(n=>{let l0=l;l+=n;return l0;});
 *   let r=Array(l);
 *   x.map((e,i)=>{if(e>=0)r[s[e]++]=i;});
 *   return list(r,x.fill);
 * }
 */
#define SYMBOL "∾⊔𝕩"
Value *GroupOrd::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG(SYMBOL ": nargs={},args={}", nargs, args);
  auto *w = dynamic_cast<Array*>(args[2]);
  auto *x = dynamic_cast<Array*>(args[1]);

  uz len = 0;
  std::vector<uz> v(w->N(), 0);
  for (int i=0; i < w->N(); i++) {
    v[i] = len;
    len += static_cast<uz>(DCN(w->values[i])->v);
  }

  std::vector<f64> retv(x->N(), 0);
  for (int i=0; i < x->N(); i++) {
    const auto e = DCN(x->values[i])->v;
    if (fge_helper(e, 0.0)) {
      const auto idx = static_cast<uz>(e);
      retv[v[idx]++] = static_cast<f64>(i);
    }
  }

  auto *ret = new Array(len);
  for (int i=0; i < x->N(); i++) {
    ret->values[i] = new Number(retv[i]);
  }
  return ret;
}
#undef SYMBOL

} // namespace cxbqn::provides
