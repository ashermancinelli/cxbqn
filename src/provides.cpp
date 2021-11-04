#include <cmath>
#include <cxbqn/debug.hpp>
#include <cxbqn/provides.hpp>

namespace cxbqn::provides {

Array *get_runtime() {
  CXBQN_DEBUG("provides::get_runtime");
  auto *rt = new Array(23);
  rt->values.resize(23);
  rt->values[0] = bi_plus();
  rt->values[1] = bi_minus();
  rt->values[2] = bi_mul();
  rt->values[3] = bi_div();
  rt->values[4] = bi_power();
  rt->values[5] = bi_root();
  rt->values[6] = bi_floor();
  rt->values[7] = bi_ceil();
  rt->values[8] = bi_stile();
  rt->values[17] = bi_feq();
  rt->values[18] = bi_fne();
  rt->values[20] = bi_ltack();
  rt->values[21] = bi_rtack();
  rt->values[48] = bi_table();
  return rt;
}

Value *bi_plus() {
  static Plus p;
  return &p;
}
Value *bi_minus() {
  static Minus m;
  return &m;
}
Value *bi_mul() {
  static Mul m;
  return &m;
}
Value *bi_div() {
  static Div d;
  return &d;
}
Value *bi_power() {
  static Power x;
  return &x;
}
Value *bi_root() {
  static Root r;
  return &r;
}
Value *bi_floor() {
  static Floor f;
  return &f;
}
Value *bi_ceil() {
  static Ceil c;
  return &c;
}
Value *bi_stile() {
  static Stile s;
  return &s;
}
Value *bi_feq() {
  static FEQ f;
  return &f;
}
Value *bi_fne() {
  static FNE f;
  return &f;
}
Value *bi_ltack() {
  static Ltack lt;
  return &lt;
}
Value *bi_rtack() {
  static Rtack rt;
  return &rt;
}
Value *bi_arraydepth() {
  static ArrayDepth f;
  return &f;
}
Value *bi_type() {
  static Type t;
  return &t;
}
Value *bi_table() {
  static Table t;
  return &t;
}

namespace {

// The t() method on all values in cxbqn uses higher bits to indicate internal
// type annotations. We only want the lowest 3 bits for the builtin •Type.
static inline auto type_builtin(const Value *v) {
  return (v->t() & TypeType{0b111}).to_ulong();
}

static inline void reshape(Array *arr, std::initializer_list<uz> shape) {
  const auto n =
      std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<uz>());
  arr->N = n;
  arr->values.resize(n);
}

} // namespace

Value *Type::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG("•Type::call:nargs={},args={}", nargs, args);
#ifdef CXBQN_DEEPCHECKS
  if (args.size() < 2)
    throw std::runtime_error("type got <2 args");
  if (nullptr == /*𝕩=*/args[1])
    throw std::runtime_error("type got nullptr for 𝕩");
#endif
  return new Number(static_cast<f64>(type_builtin(args[1])));
}

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

namespace {
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

static bool feq_helper(f64 a, f64 b) {
  return std::abs(a - b) < std::numeric_limits<f64>::epsilon();
}

} // namespace

Value *ArrayDepth::call(u8 nargs, std::vector<Value *> args) {
  return new Number(static_cast<f64>(array_depth_helper(0, args[1])));
}

Value *Plus::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG("+:nargs={},args={}", nargs, args);
  if (1 == nargs)
    return args[1];

  auto *x = dynamic_cast<Number *>(args[1]);
  auto *w = dynamic_cast<Number *>(args[2]);
  return new Number(x->v + w->v);
}

Value *Minus::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG("-:nargs={},args={}", nargs, args);
  auto *x = dynamic_cast<Number *>(args[1]);
  auto *w = dynamic_cast<Number *>(args[2]);
  return new Number(2 == nargs ? w->v - x->v : -x->v);
}

Value *Mul::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG("×:nargs={},args={}", nargs, args);
  auto *x = dynamic_cast<Number *>(args[1]);
  auto *w = dynamic_cast<Number *>(args[2]);
  if (2 == nargs) {
    return new Number(w->v * x->v);
  }
  return new Number(feq_helper(0.0, x->v) ? 0 : x->v > 0 ? 1 : 0);
}

Value *Div::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG("÷:nargs={},args={}", nargs, args);
  auto *x = dynamic_cast<Number *>(args[1]);
  auto *w = dynamic_cast<Number *>(args[2]);
  return new Number(2 == nargs ? w->v / x->v : 1 / x->v);
}

Value *Power::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG("÷:nargs={},args={}", nargs, args);
  auto *x = dynamic_cast<Number *>(args[1]);
  auto *w = dynamic_cast<Number *>(args[2]);
  return new Number(2 == nargs ? std::pow(w->v, x->v) : std::exp(x->v));
}

Value *Root::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG("÷:nargs={},args={}", nargs, args);
  auto *x = dynamic_cast<Number *>(args[1]);
  auto *w = dynamic_cast<Number *>(args[2]);
  return new Number(2 == nargs ? std::pow(x->v, 1 / w->v)
                                     : std::sqrt(x->v));
}

Value *Floor::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG("⌊:nargs={},args={}", nargs, args);
  auto *x = dynamic_cast<Number *>(args[1]);
  auto *w = dynamic_cast<Number *>(args[2]);
  if (2 == nargs) {
    return new Number(std::min(w->v, x->v));
  }
  return new Number(std::floor(x->v));
}

Value *Ceil::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG("⌈:nargs={},args={}", nargs, args);
  auto *x = dynamic_cast<Number *>(args[1]);
  auto *w = dynamic_cast<Number *>(args[2]);
  if (2 == nargs) {
    return new Number(std::max(w->v, x->v));
  }
  return new Number(std::ceil(x->v));
}

Value *Stile::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG("⌈:nargs={},args={}", nargs, args);
  auto *x = dynamic_cast<Number *>(args[1]);
  auto *w = dynamic_cast<Number *>(args[2]);
  if (2 == nargs) {
    return new Number(std::max(w->v, x->v));
  }
  return new Number(2 == nargs ? std::fmod(w->v, x->v) : std::abs(x->v));
}

Value *FEQ::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG("feq:nargs={},args={}", nargs, args);
  auto *x = dynamic_cast<Number *>(args[1]);
  auto *w = dynamic_cast<Number *>(args[2]);
  return new Number(static_cast<f64>(feq_helper(x->v, w->v)));
}

Value *FNE::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG("fne:nargs={},args={}", nargs, args);
  auto *x = dynamic_cast<Number *>(args[1]);
  auto *w = dynamic_cast<Number *>(args[2]);
  return new Number(static_cast<f64>(!feq_helper(x->v, w->v)));
}

Value *Ltack::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG("⊣:nargs={},args={}", nargs, args);
  return args[2];
}

Value *Rtack::call(u8 nargs, std::vector<Value *> args) {
  CXBQN_DEBUG("⊢:nargs={},args={}", nargs, args);
  return args[1];
}

// Value *Type::call(u8 nargs, std::vector<Value *> args) { }

} // namespace cxbqn::provides
