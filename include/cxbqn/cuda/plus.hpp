#include <cxbqn/types.hpp>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>

namespace cxbqn::cuda {

__global__ static inline void Plus(f64* x, f64* w, std::size_t N) {
  std::size_t i = threadIdx.x;
  x[i] = x[i] + w[i];
}

} // namespace cxbqn::cuda
