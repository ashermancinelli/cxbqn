#include "provides_helpers.hpp"

namespace cxbqn::provides {

O<Value> Decompose::call(u8 nargs, std::vector<O<Value>> args) {
  CXBQN_DEBUG("Decompose: nargs={},args={}", nargs, args);
  XNULLCHK("•Decompose");
  if (2 == nargs)
    throw std::runtime_error("Decompose: expected one argument, got two");

  auto x = args[1];

  // Check for data values
  if (x->t()[t_DataValue])
    return O<Value>(new Array({NNC(-1), x}));

  // Check for primitives
  auto it = std::find(runtime.begin(), runtime.end(), x);

  if (it != runtime.end())
    return O<Value>(new Array({NNC(0), x}));

  if (auto xx = dynamic_pointer_cast<Atop>(x))
    return O<Value>(new Array({NNC(2), xx->f, xx->g}));

  if (auto xx = dynamic_pointer_cast<Fork>(x))
    return O<Value>(new Array({NNC(3), xx->f, xx->g, xx->h}));

  if (auto xx = dynamic_pointer_cast<Md1Deferred>(x))
    return O<Value>(new Array({NNC(4), xx->f, xx->m1}));

  if (auto xx = dynamic_pointer_cast<Md2Deferred>(x))
    return O<Value>(new Array({NNC(5), xx->f, xx->m2, xx->g}));

  return O<Value>(new Array({NNC(1), args[1]}));
}
}
