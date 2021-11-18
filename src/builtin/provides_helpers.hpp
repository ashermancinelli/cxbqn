#pragma once
#include <cmath>
#include <cxbqn/debug.hpp>
#include <spdlog/fmt/fmt.h>
#include <cxbqn/cxbqn.hpp>

#ifdef CXBQN_DEEPCHECKS
#define XNULLCHK(SYMBOL)                                                       \
  do {                                                                         \
    if (args[1]->t()[t_Nothing])                                               \
      throw std::runtime_error(SYMBOL ": got · for 𝕩");                        \
  } while (0);
#else
#define XNULLCHK(SYMBOL) (void)0
#endif

// I promise this makes the definitions more readable :)
#define NN(x) make_shared<Number>(x)

// "new number casted", creates a new number after casting some expression into
// an f64
#define NNC(x) make_shared<Number>(static_cast<f64>(x))

namespace cxbqn::provides {

bool eq_recursive(O<Value> ox, O<Value> ow);

// The t() method on all values in cxbqn uses higher bits to indicate internal
// type annotations. We only want the lowest 3 bits for the builtin •Type.
inline auto type_builtin(const O<Value> v) {
  return (v->t() & TypeType{0b111}).to_ulong();
}

#define CHR_MAX 1114111
O<Value> check_char(O<Value> v);

// Recursively find the max depth of each element, and max reduce
uz array_depth_helper(uz init, O<Value> v);

// For floating point comparisons, we use 10 times the machine precision.
// Subject to change.
template <typename T = f64> bool feq_helper(T a, T b) {
#define INF std::numeric_limits<T>::infinity()
  if (a == INF and b == INF)
    return true;
  if (a == -INF and b == -INF)
    return true;
#undef INF
  return std::abs(a - b) < (10 * std::numeric_limits<T>::epsilon());
}

bool equivilant_helper(O<Value> a, O<Value> b);

template <typename T = f64> bool fge_helper(T a, T b) {
  return feq_helper(a, b) or a > b;
}

template <typename T = f64> bool fle_helper(T a, T b) {
  return feq_helper(a, b) or a < b;
}

}
