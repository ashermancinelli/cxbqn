#include <cxbqn/types.hpp>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>

namespace cxbqn::cuda {

#define CXBQN_DEVICE_ARITH_FN(NAME, DYA, MON)                                  \
  __global__ static void NAME(f64 *xx, f64 *ww, std::size_t N) {               \
    std::size_t i = threadIdx.x;                                               \
    auto x = xx[i], w = ww[i];                                                 \
    xx[i] = DYA;                                                                \
  }                                                                            \
  __global__ static void NAME(f64 *xx, std::size_t N) {                        \
    std::size_t i = threadIdx.x;                                               \
    auto x = xx[i];                                                            \
    xx[i] = MON;                                                                \
  }

// +-×÷⋆√⌊⌈|¬
CXBQN_DEVICE_ARITH_FN(plus, x + w, x);
CXBQN_DEVICE_ARITH_FN(minus, w - x, -x);
CXBQN_DEVICE_ARITH_FN(mul, w*x, (0.f==x?0:x>0?1:0));
CXBQN_DEVICE_ARITH_FN(div, w / x, 1/x);
CXBQN_DEVICE_ARITH_FN(power, pow(w, x), exp(x));
CXBQN_DEVICE_ARITH_FN(root, pow(x, 1/w), sqrt(x));
CXBQN_DEVICE_ARITH_FN(floor, std::min(w, x), std::floor(x))
CXBQN_DEVICE_ARITH_FN(ceil, std::max(w, x), std::ceil(x))
CXBQN_DEVICE_ARITH_FN(stile, w/x, 1/x);
CXBQN_DEVICE_ARITH_FN(not_, 1+(w-x), 1-x);
} // namespace cxbqn::cuda
