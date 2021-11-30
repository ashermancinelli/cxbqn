#include "sys_helper.hpp"
#include <cxbqn/cuda/plus.hpp>
#include <cuda.h>
#include <thrust/device_free.h>
#include <thrust/device_malloc.h>
#include <thrust/device_ptr.h>
#include <thrust/device_vector.h>
#include <thrust/iterator/zip_iterator.h>
#include <thrust/tuple.h>

using namespace thrust;

namespace cxbqn::sys {
O<Value> CUDAFor::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("•_CUDAFor: nargs={},args={}", nargs, args);
  auto x = args[1];
  auto f = args[4];
  auto w = args[2];
  auto it = std::find(_runtime->values.begin(), _runtime->values.end(), f);
  auto xind = std::distance(_runtime->values.begin(), it);

  auto xar = dyncast<Array>(x);
  auto war = dyncast<Array>(w);
  if (xar->N() != war->N())
    throw std::runtime_error("•_CUDAFor: 𝕩 and 𝕨 must have matching shapes");
  if (1 == nargs)
    throw std::runtime_error("•_CUDAFor: only dyadic calls");

  const std::size_t N = xar->N();

  thrust::host_vector<f64> hx(N);
  thrust::host_vector<f64> hw(N);
  for (int i = 0; i < N; i++) {
    hx[i] = dyncast<Number>(xar->values[i])->v;
    hw[i] = dyncast<Number>(war->values[i])->v;
  }
  thrust::device_vector<f64> dx = hx;
  thrust::device_vector<f64> dw = hw;
  cuda::Plus<<<1, N>>>(raw_pointer_cast(dx.data()), raw_pointer_cast(dw.data()), N);
  // cuda::Plus<<<1, 5>>>(nullptr, nullptr, 10);
  hx = dx;
  O<Array> ret = CXBQN_NEW(Array, N);
  for (int i = 0; i < N; i++)
    ret->values[i] = CXBQN_NEW(Number, hx[i]);

  return ret;
#if 0
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
  switch (type_builtin(x)) {
  case t_Array: {
    auto ax = dyncast<Array>(x);
    thrust::host_vector<f64> h(ax->N());
    for(int i=0, auto e=ax->values[i]; i<ax->N(); i++, e=ax->values[i]) {
#ifdef CXBQN_DEEPCHECKS
      u8 ee;
      if (t_Number != (ee=type_builtin(e)) and t_Character != ee)
        throw std::runtime_error("•_CUDAFor only accepts non-nested arrays of numbers or chars for 𝕩");
#endif
      h[i] = dyncast<Number>(e)->v;
      thrust::device_vector<f64> d = h;
      // thrust::transform(d.begin(), d.end(), d.begin(), cuda::Plus);
    }
    break;
  }
  case t_Number:
  case t_Character: {
    auto dx = dyncast<Number>(x)->v;
    break;
  }
  default: {
    throw std::runtime_error("•_CUDAFor only accepts data values for 𝕩");
  }
  }
  return CXBQN_NEW(Number, 1);
#endif
}
} // namespace cxbqn::sys
