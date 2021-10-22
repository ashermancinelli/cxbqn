#pragma once

namespace cxbqn::value_types {

template<ValueType VT>
struct Value {
  std::optional<uint64_t> decode() {
    return VT::decode();
  }
};

}
