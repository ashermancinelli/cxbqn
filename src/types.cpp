#include <types.hpp>

namespace cxbqn::types {

Array::Array() : values{nullptr} { }

Array::Array(initl<f64> vs) {
  shape.push_back(vs.size());
  values = new f64[vs.size()];
  std::copy(vs.begin(), vs.end(), values);
}

Array::Array(initl<uz> szs, initl<f64> vs) {
  std::copy(szs.begin(), szs.end(), std::back_inserter(shape));
  uz len = std::accumulate(szs.begin(), szs.end(), 1, std::multiplies<uz>());
  values = new f64[len];
  std::copy(vs.begin(), vs.end(), values);
}

Array::~Array() {
  if (nullptr == values)
    return;
  delete[] values;
}

Block::Block(uz ty, uz immediate, uz idx)
    : type{static_cast<BlockType>(ty)}, immediate{static_cast<bool>(immediate)},
      comp{nullptr}, body_idx{idx} {}

Block::~Block() {}

} // namespace cxbqn::types
