#pragma once
#include <cxbqn/config.hpp>
#include <cxbqn/types.hpp>
#include <tuple>

namespace {

template <typename T> static constexpr TypeType typed_array_annot();

template <> static constexpr TypeType typed_array_annot<i64>() {
  return annot(t_I64Array);
}
template <> static constexpr TypeType typed_array_annot<f64>() {
  return annot(t_F64Array);
}
template <> static constexpr TypeType typed_array_annot<uz>() {
  return annot(t_UZArray);
}
template <> static constexpr TypeType typed_array_annot<c32>() {
  return annot(t_C32Array);
}

} // namespace

namespace cxbqn::types {

template <typename T> struct TypedArray : public ArrayBase {
  using value_type = T;
  std::vector<T> values;
  std::vector<uz> _shape;
  TypedArray(uz N) {
    _shape.push_back(N);
    values.resize(N);
  }
  TypedArray(std::vector<T> vals, std::vector<uz> shape)
      : values{vals}, _shape{shape} {}
  TypedArray(std::vector<T> vals) : values{vals} {
    _shape.push_back(vals.size());
  }

  Array() {}
  ~Array() {}

  O<Value> get(uz i) const override {
    return CXBQN_NEW(Number, values[i]);
  }

  uz N() const override {
    return values.size();
  }

  std::vector<uz> &shape() const override {
    return _shape;
  }

  O<ArrayBase> copy() const override {
    return CXBQN_NEW(TypedArray<T>, values, _shape);
  }

  static constexpr TypeType extra_annot = typed_array_annot<T>();

  inline TypeType t() const override {
    return TypeType{t_Array | annot(t_TypedArray) | extra_annot};
  }

  std::ostream &repr(std::ostream &os) const override;
};

using String = TypedArray<c32>;

} // namespace cxbqn::types
