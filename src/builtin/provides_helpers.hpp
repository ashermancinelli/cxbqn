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

namespace cxbqn::provides {
// The t() method on all values in cxbqn uses higher bits to indicate internal
// type annotations. We only want the lowest 3 bits for the builtin •Type.
inline auto type_builtin(const O<Value> v) {
  return (v->t() & TypeType{0b111}).to_ulong();
}
}
