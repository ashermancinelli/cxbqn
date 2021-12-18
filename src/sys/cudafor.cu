#include "sys_helper.hpp"
#include <cuda.h>
#include <cxbqn/cuda/all.hpp>
#include <thrust/device_free.h>
#include <thrust/device_malloc.h>
#include <thrust/device_ptr.h>
#include <thrust/device_vector.h>
#include <thrust/iterator/zip_iterator.h>
#include <thrust/tuple.h>

using namespace thrust;

namespace {
void call_inl(std::size_t rt_idx, f64 *x, f64 *w, std::size_t N) {
  // +-×÷⋆√⌊⌈|¬
  switch (rt_idx) {
  case 0: cxbqn::cuda::plus<<<1, N>>>(x, w, N); return;
  case 1: cxbqn::cuda::minus<<<1, N>>>(x, w, N); return;
  case 2: cxbqn::cuda::mul<<<1, N>>>(x, w, N); return;
  case 3: cxbqn::cuda::div<<<1, N>>>(x, w, N); return;
  case 4: cxbqn::cuda::power<<<1, N>>>(x, w, N); return;
  case 5: cxbqn::cuda::root<<<1, N>>>(x, w, N); return;
  case 6: cxbqn::cuda::floor<<<1, N>>>(x, w, N); return;
  case 7: cxbqn::cuda::ceil<<<1, N>>>(x, w, N); return;
  case 8: cxbqn::cuda::stile<<<1, N>>>(x, w, N); return;
  case 9: cxbqn::cuda::not_<<<1, N>>>(x, w, N); return;

  // ∧∨<>≠=≤≥≡≢
  // case 9: cxbqn::cuda::not_<<<1, N>>>(x, w, N); return;

  default:
    throw std::runtime_error("•_CUDAFor: 𝕗 unsupported in device code");
  }
}
} // namespace

namespace cxbqn::sys {
O<Value> CUDAFor::call(u8 nargs, Args &args) {
  CXBQN_DEBUG("•_CUDAFor: nargs={},args={}", nargs, args);
  if (1 == nargs)
    throw std::runtime_error("•_CUDAFor: only dyadic calls");
  auto x = args[1];
  auto f = args[4];
  auto w = args[2];
  auto it = std::find(_runtime->values.begin(), _runtime->values.end(), f);
  auto xind = std::distance(_runtime->values.begin(), it);

  thrust::device_vector<f64> hx;
  thrust::device_vector<f64> hw;

  int N=-1;
  bool isxar=false,iswar=false;
  std::vector<uz> sh;

  if (isxar = (t_Array == type_builtin(x))) {
    auto xar = dyncast<Array>(x);
    N = xar->N();
    sh = xar->shape;
    hx.resize(N);
    hw.resize(N);
    for (int i = 0; i < N; i++)
      hx[i] = dyncast<Number>(xar->values[i])->v;
    N = xar->N();
  } 
  if (iswar = (t_Array == type_builtin(w))) {
    auto war = dyncast<Array>(w);
    if (N<0) {
      N = war->N();
      sh = war->shape;
      hx.resize(N);
      hw.resize(N);
    }
    else if (N != war->N())
      throw std::runtime_error("•_CUDAFor: array lengths must be the same");
    for (int i = 0; i < N; i++)
      hw[i] = dyncast<Number>(war->values[i])->v;
  } 

  if (N < 0) {
    N = 1;
    hx.resize(N);
    hw.resize(N);
    sh.push_back(1);
  }

  if (not isxar) {
    auto v = dyncast<Number>(x)->v;
    for (int i = 0; i < N; i++)
      hx[i] = v;
  }
  if (not iswar) {
    auto v = dyncast<Number>(w)->v;
    for (int i = 0; i < N; i++)
      hw[i] = v;
  }

  thrust::device_vector<f64> dx = hx;
  thrust::device_vector<f64> dw = hw;
  call_inl(xind, raw_pointer_cast(dx.data()), raw_pointer_cast(dw.data()), N);
  hx = dx;

  O<Array> ret = CXBQN_NEW(Array, N);
  ret->shape = sh;
  for (int i = 0; i < N; i++)
    ret->values[i] = CXBQN_NEW(Number, hx[i]);

  return ret;
}
} // namespace cxbqn::sys
