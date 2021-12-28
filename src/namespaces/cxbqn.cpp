#include <cxbqn/types.hpp>
#include <cxbqn/namespaces/cxbqn.hpp>
#include <cxbqn/namespaces/cxbqn/plot.hpp>
#include <cxbqn/config.hpp>

namespace cxbqn::namespaces {

O<Value> CXBQN::get(const std::string &n) {
  if (_exported.contains(n))
    return _exported.at(n);
  throw std::runtime_error(fmt::format("•cxbqn: could not find name {}", n));
}

CXBQN::CXBQN() {
  auto config = CXBQN_NEW(Array);

  {
    auto rl = CXBQN_NEW(Array, 2);
    rl->values[0] = CXBQN_NEW(Array, "CXBQN_READLINE");
    rl->values[1] =
#ifdef CXBQN_READLINE
      CXBQN_NEW(Number, 1);
#else
      CXBQN_NEW(Number, 0);
#endif
    config->values.push_back(rl);
  }

  {
    auto cuda = CXBQN_NEW(Array, 2);
    cuda->values[0] = CXBQN_NEW(Array, "CXBQN_CUDA");
    cuda->values[1] =
#ifdef CXBQN_CUDA
      CXBQN_NEW(Number, 1);
#else
      CXBQN_NEW(Number, 0);
#endif
    config->values.push_back(cuda);
  }

  {
    auto ffi = CXBQN_NEW(Array, 2);
    ffi->values[0] = CXBQN_NEW(Array, "CXBQN_FFI");
    ffi->values[1] =
#ifdef CXBQN_FFI
      CXBQN_NEW(Number, 1);
#else
      CXBQN_NEW(Number, 0);
#endif
    config->values.push_back(ffi);
  }

  {
    auto plot = CXBQN_NEW(Array, 2);
    plot->values[0] = CXBQN_NEW(Array, "CXBQN_PLOT");
    plot->values[1] =
#ifdef CXBQN_PLOT
      CXBQN_NEW(Number, 1);
#else
      CXBQN_NEW(Number, 0);
#endif
    config->values.push_back(plot);
  }

  config->shape().push_back(config->values.size());

  _exported.insert({"config", config});
#ifdef CXBQN_PLOT
  _exported.insert({"plot", CXBQN_NEW(namespaces::cxbqn::Plot)});
#endif
}

}
