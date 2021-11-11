#include <cmath>
#include <cxbqn/debug.hpp>
#include <cxbqn/fmt.hpp>
#include <cxbqn/provides.hpp>

namespace cxbqn::provides {

namespace {

// The t() method on all values in cxbqn uses higher bits to indicate internal
// type annotations. We only want the lowest 3 bits for the builtin •Type.
static inline auto type_builtin(const O<Value> v) {
  return (v->t() & TypeType{0b111}).to_ulong();
}

#define CHR_MAX 1114111
static inline O<Value> check_char(O<Value> v) {
  if (t_Character != type_builtin(v))
    throw std::runtime_error("internal: invalid value passed to check_char");
  auto f = std::dynamic_pointer_cast<Character>(v)->v;
  if (f < 0 || f > CHR_MAX)
    throw std::runtime_error("invalid code point");
  return v;
}

// Recursively find the max depth of each element, and max reduce
static uz array_depth_helper(uz init, O<Value> v) {
  CXBQN_DEBUG("array_depth_helper:init={},value={}", init, CXBQN_STR_NC(v));
  if (t_Array == type_builtin(v)) {
    auto ar = std::dynamic_pointer_cast<Array>(v);
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

static bool equivilant_helper(O<Value> a, O<Value> b) {
  if (a->t()[t_DataValue] and b->t()[t_DataValue])
    return feq_helper(std::dynamic_pointer_cast<Number>(a)->v,
                      std::dynamic_pointer_cast<Number>(b)->v);
  else if (t_Array == type_builtin(a) and t_Array == type_builtin(b)) {
    auto av = std::dynamic_pointer_cast<Array>(a);
    auto bv = std::dynamic_pointer_cast<Array>(b);
    if (av->N() != bv->N())
      return false;
    for (int i = 0; i < av->N(); i++)
      if (!equivilant_helper(av->values[i], bv->values[i]))
        return false;
  }
  throw std::runtime_error("equivilant_helper: something went wrong");
  return false;
}

template <typename T = f64> static bool fge_helper(T a, T b) {
  return feq_helper(a, b) or a > b;
}

template <typename T = f64> static bool fle_helper(T a, T b) {
  return feq_helper(a, b) or a < b;
}

} // namespace

// I promise this makes the definitions more readable :)
#define NN(x) make_shared<Number>(x)

// "new number casted", creates a new number after casting some expression into
// an f64
#define NNC(x) make_shared<Number>(static_cast<f64>(x))

// "dynamic cast to a number"
#define DCN(x) std::dynamic_pointer_cast<Number>(x)

// Shorthand to define the call method of a given builtin type.
// `ox` and `ow` are short for the opaque pointers to each argument, in case the
// operator needs to do some checks on the values before casting them.
#define CXBQN_BI_CALL_DEF_NUMONLY(TYPE, SYMBOL, PREAMBLE, RETURN)              \
  O<Value> TYPE::call(u8 nargs, std::vector<O<Value>> args) {                  \
    CXBQN_DEBUG(SYMBOL ":nargs={},args={}", nargs, args);                      \
    auto ox = args[1];                                                         \
    auto ow = args[2];                                                         \
    auto x = std::dynamic_pointer_cast<Number>(args[1]);                       \
    auto w = std::dynamic_pointer_cast<Number>(args[2]);                       \
    PREAMBLE;                                                                  \
    auto ret = (RETURN);                                                       \
    return ret;                                                                \
  }

O<Value> Plus::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("+:nargs={},args={}", nargs, args);
  auto ox = args[1];
  auto ow = args[2];
  if (1 == nargs)
    return ox;

  /* compare by value for data types */
  auto x = std::dynamic_pointer_cast<Number>(ox);
  auto w = std::dynamic_pointer_cast<Number>(ow);

  if (t_Character == type_builtin(ox) and t_Character == type_builtin(ow))
    throw std::runtime_error("+: Cannot add two characters");
  if (!ox->t()[t_DataValue] or !ow->t()[t_DataValue]) {
    CXBQN_CRIT("Got x={}, w={}", CXBQN_STR_NC(ox), CXBQN_STR_NC(ow));
    throw std::runtime_error("+: Cannot add non-data values.");
  }
  if (t_Character == type_builtin(ox) || t_Character == type_builtin(ow)) {
    return check_char(make_shared<Character>(x->v + w->v));
  }
  return NN(x->v + w->v);
}

CXBQN_BI_CALL_DEF_NUMONLY(
    Minus, "-",
    {
      if (t_Character == type_builtin(ow) and t_Number == type_builtin(ox)) {
        return check_char(make_shared<Character>(w->v - x->v));
      }
      if (t_Character == type_builtin(ow) and t_Character == type_builtin(ox)) {
        return make_shared<Number>(w->v - x->v);
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

O<Value> EQ::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("=:nargs={},args={}", nargs, args);
  auto ox = args[1];
  auto ow = args[2];

  if (1 == nargs and t_Array == type_builtin(ox))
    return make_shared<Number>(
        (static_cast<f64>(std::dynamic_pointer_cast<Array>(ox)->shape.size())));

  if (1 == nargs)
    return args[1];

  /* If the builtin types differ, that's an easy case to rule out */
  if (type_builtin(ox) != type_builtin(ow))
    return NNC(false);

  /* pointer comparison for functions and modifiers */
  if (auto xf = std::dynamic_pointer_cast<Fork>(ox)) {
    auto wf = std::dynamic_pointer_cast<Fork>(ow);
    return NNC(xf->f == wf->f && xf->g == wf->g && xf->h == wf->h);
  }
  if (auto xf = std::dynamic_pointer_cast<Atop>(ox)) {
    auto wf = std::dynamic_pointer_cast<Atop>(ow);
    return NNC(xf->f == wf->f && xf->g == wf->g);
  }
  if (auto xf = std::dynamic_pointer_cast<Md2Deferred>(ox)) {
    auto wf = std::dynamic_pointer_cast<Md2Deferred>(ow);
    return NNC(xf->f == wf->f && xf->m2 == wf->m2 && xf->g == wf->g);
  }
  if (auto xf = std::dynamic_pointer_cast<Md1Deferred>(ox)) {
    auto wf = std::dynamic_pointer_cast<Md1Deferred>(ow);
    return NNC(xf->f == wf->f && xf->m1 == wf->m1);
  }

  // If it's none of the types we check for above, it's gotta be a number/char
  return NNC(feq_helper(std::dynamic_pointer_cast<Number>(ox)->v,
                        std::dynamic_pointer_cast<Number>(ow)->v));
}

CXBQN_BI_CALL_DEF_NUMONLY(LE, "≤", {},
                          NNC(w->v < x->v || feq_helper(x->v, w->v)));
CXBQN_BI_CALL_DEF_NUMONLY(GE, "≥", {},
                          NNC(w->v > x->v || feq_helper(x->v, w->v)));
CXBQN_BI_CALL_DEF_NUMONLY(Ltack, "⊣", {}, args[2]);
CXBQN_BI_CALL_DEF_NUMONLY(Rtack, "⊣", {}, args[1]);
CXBQN_BI_CALL_DEF_NUMONLY(Type, "•Type", {}, NNC(type_builtin(args[1])));

O<Value> FEQ::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("≡:nargs={},args={}", nargs, args);
  return NNC(equivilant_helper(args[1], args[2]));
}
O<Value> FNE::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("≢:nargs={},args={}", nargs, args);
  if (2 == nargs)
    throw std::runtime_error("≢: provided function expected only one arg");
  auto arr = std::dynamic_pointer_cast<Array>(args[1]);
  auto ret = make_shared<Array>(arr->shape.size());
  for (int i = 0; i < ret->N(); i++)
    ret->values[i] = make_shared<Number>(static_cast<f64>(arr->shape[i]));
  return ret;
}

O<Value> Table::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("⌜: nargs={},args={}", nargs, args);
  auto F = args[4];
  if (t_Array != type_builtin(args[1]) or t_Array != type_builtin(args[2]))
    throw std::runtime_error("⌜: 𝕩 and 𝕨 must be arrays");

  auto x = std::dynamic_pointer_cast<Array>(args[1]);
  const auto &xv = x->values;

  if (1 == nargs) {
    auto ret = make_shared<Array>(x->N());
    for (int i = 0; i < x->N(); i++)
      ret->values[i] = F->call(1, {F, x->values[i], bi_Nothing()});
    return ret;
  }

  auto w = std::dynamic_pointer_cast<Array>(args[2]);
  const auto &wv = w->values;
  auto ret = make_shared<Array>(x->N() * w->N());
  for (int iw = 0; iw < w->N(); iw++)
    for (int ix = 0; ix < x->N(); ix++) {
      ret->values[(iw * x->N()) + ix] = F->call(2, {F, xv[ix], wv[iw]});
    }
  ret->shape.assign(w->shape.begin(), w->shape.end());
  ret->shape.insert(ret->shape.end(), x->shape.begin(), x->shape.end());
  return ret;
}

O<Value> ArrayDepth::call(u8 nargs, std::vector<O<Value>> args) {
  return make_shared<Number>(static_cast<f64>(array_depth_helper(0, args[1])));
}

CXBQN_BI_CALL_DEF_NUMONLY(Fill, "Fill", {}, 2 == nargs ? args[1] : NN(0));
CXBQN_BI_CALL_DEF_NUMONLY(Log, "Log", {},
                          2 == nargs ? NN(std::log(w->v) / std::log(x->v))
                                     : NN(std::log(x->v)));
O<Value> Assert::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("!: nargs={},args={}", nargs, args);
  bool shoulddie = false;
  if (t_Number != type_builtin(args[1]))
    shoulddie = true;
  if (!feq_helper(1., std::dynamic_pointer_cast<Number>(args[1])->v))
    shoulddie = true;
  if (shoulddie) {
    CXBQN_CRIT("{} ! {}", (2 == nargs ? CXBQN_STR_NC(args[2]) : ""),
               CXBQN_STR_NC(args[1]));
    throw std::runtime_error("!");
  }
  return args[1];
}

O<Value> Range::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("↕: nargs={},args={}", nargs, args);
  auto n = static_cast<uz>(std::dynamic_pointer_cast<Number>(args[1])->v);
  auto arr = make_shared<Array>(n);
  for (int i = 0; i < arr->N(); i++)
    arr->values[i] = make_shared<Number>(i);
  return arr;
}

O<Value> Pick::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("⊑: nargs={},args={}", nargs, args);
  auto n = static_cast<uz>(std::dynamic_pointer_cast<Number>(args[2])->v);
  return std::dynamic_pointer_cast<Array>(args[1])->values[n];
}

O<Value> Shape::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("≢: nargs={},args={}", nargs, args);
  auto ret = make_shared<Array>();
  auto sh = std::dynamic_pointer_cast<Array>(args[1])->shape;
  ret->values.resize(sh.size());
  for (int i = 0; i < sh.size(); i++)
    ret->values[i] = make_shared<Number>(sh[i]);
  return ret;
}

O<Value> Deshape::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("⥊: nargs={},args={}", nargs, args);

  const bool iswarr = t_Array == type_builtin(args[2]);
  const bool isxarr = t_Array == type_builtin(args[1]);
  auto xarr = isxarr ? std::dynamic_pointer_cast<Array>(args[1]) : nullptr;

  if (1 == nargs) {
    if (isxarr) {
      xarr->shape.assign({xarr->N()});
      return xarr;
    } else {
      return std::shared_ptr<Array>(new Array({args[1]}));
    }
  }

  auto ret = make_shared<Array>();
  if (iswarr) {
    auto warr = std::dynamic_pointer_cast<Array>(args[2]);
    for (int i = 0; i < warr->N(); i++)
      ret->shape.push_back(static_cast<uz>(
          std::dynamic_pointer_cast<Number>(warr->values[i])->v));
  } else {
    ret->shape.push_back(
        static_cast<uz>(std::dynamic_pointer_cast<Number>(args[2])->v));
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

O<Value> Scan::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("`: nargs={},args={}", nargs, args);
  if (t_Array != type_builtin(args[1]))
    throw std::runtime_error("`: 𝕩 must have rank at least 1");

  auto x = std::dynamic_pointer_cast<Array>(args[1]);
  auto w = args[2];
  auto F = args[4];

  auto sh = x->shape;
  auto iswarr = (t_Array == type_builtin(w));
  if (2 == nargs) {
    auto w_rank =
        iswarr ? std::dynamic_pointer_cast<Array>(w)->shape.size() : 0;
    if (1 + w_rank != x->shape.size())
      throw std::runtime_error("`: rank of 𝕨 must be cell rank of 𝕩");
    if (iswarr) {
      const auto &wsh = std::dynamic_pointer_cast<Array>(w)->shape;
      for (int i = 0; i < x->shape.size() - 1; i++)
        if (wsh[i] != x->shape[i + 1])
          throw std::runtime_error("`: shape of 𝕨 must be cell shape of 𝕩");
    }
  }

  auto ret = make_shared<Array>();
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
  auto warr = iswarr ? std::dynamic_pointer_cast<Array>(w)
                     : std::shared_ptr<Array>(new Array({w}));
  CXBQN_DEBUG("cnt={},warr={}", cnt, CXBQN_STR_NC((O<Value>)warr));
  if (1 == nargs)
    for (; i < cnt; i++)
      ret->values[i] = x->values[i];
  else
    for (; i < cnt; i++) {
      auto xv = x->values[i];
      auto wv = warr->values[i];
      CXBQN_DEBUG("xv={},wv={},i={}", CXBQN_STR_NC(xv), CXBQN_STR_NC(wv), i);
      ret->values[i] = F->call(2, {F, x->values[i], warr->values[i]});
    }

  for (; i < x->N(); i++)
    ret->values[i] = F->call(2, {F, x->values[i], ret->values[i - cnt]});
  return ret;
}

#define SYMBOL "GroupLen"
O<Value> GroupLen::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG(SYMBOL ": nargs={},args={}", nargs, args);
  auto x = std::dynamic_pointer_cast<Array>(args[1]);
  auto w =
      std::dynamic_pointer_cast<Number>(args[2]); // only use if nargs == 2!
  const auto init = (2 == nargs ? w->v : 0) - 1;
  std::vector<f64> xs(x->N(), 0);
  for (int i = 0; i < x->N(); i++)
    xs[i] = DCN(x->values[i])->v;
  const auto l = std::accumulate(xs.begin(), xs.end(), init,
                                 [](auto a, auto b) { return std::max(a, b); });
  std::vector<f64> retv(static_cast<uz>(l + 1), 0);
  std::fill(retv.begin(), retv.end(), 0);
  for (auto e : xs)
    if (fge_helper(e, 0.0))
      retv[static_cast<uz>(e)]++;
  auto ret = make_shared<Array>(retv.size());
  for (int i = 0; i < ret->N(); i++)
    ret->values[i] = NN(retv[i]);
  return ret;
}
#undef SYMBOL

#define SYMBOL "GroupOrd"
O<Value> GroupOrd::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG(SYMBOL ": nargs={},args={}", nargs, args);
  auto w = std::dynamic_pointer_cast<Array>(args[2]);
  auto x = std::dynamic_pointer_cast<Array>(args[1]);

  std::vector<uz> tmp(w->N(), 0);
  CXBQN_DEBUG("wn={},xn={},tmpn={}", w->N(), x->N(), tmp.size());
  for (int i = 1; i < w->N(); i++) {
    tmp[i] = tmp[i - 1] + static_cast<uz>(DCN(w->values[i - 1])->v);
    CXBQN_DEBUG("tmp[{}]={} w[i]={}", i, tmp[i],
                CXBQN_STR_NC(w->values[i - 1]));
  }

  const auto retlen = tmp.back() + static_cast<uz>(DCN(w->values.back())->v);
  CXBQN_DEBUG("return len={}", retlen);

  std::vector<f64> retv(retlen, 0);
  for (int i = 0; i < x->N(); i++) {
    const auto e = DCN(x->values[i])->v;
    if (fge_helper(e, 0.0)) {
      const auto idx = static_cast<uz>(e);
      retv[tmp[idx]++] = static_cast<f64>(i);
    }
  }

  auto ret = make_shared<Array>(retlen);
  for (int i = 0; i < retlen; i++) {
    ret->values[i] = make_shared<Number>(retv[i]);
  }
  return ret;
}
#undef SYMBOL

O<Value> FillBy::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("_fillBy_: nargs={},args={}", nargs, args);
  auto F = args[4];
  return F->call(nargs, {F, args[1], args[2]});
}

O<Value> Catch::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("⎊: nargs={},args={}", nargs, args);
  try {
    auto F = args[4];
    auto ret = F->call(nargs, {F, args[1], args[2]});
    return ret;
  } catch (std::exception &e) {
    auto G = args[5];
    auto ret = G->call(nargs, {G, args[1], args[2]});
    return ret;
  }
}

O<Value> Valence::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("⊘: nargs={},args={}", nargs, args);
  return 1 == nargs ? args[4]->call(1, {args[4], args[1], bi_Nothing()})
                    : args[5]->call(2, {args[5], args[1], args[2]});
}

} // namespace cxbqn::provides
