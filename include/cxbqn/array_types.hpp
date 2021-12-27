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

template <typename T> struct TypedArray : public Value {
  using array_type = T;
  std::vector<T> values;
  std::vector<uz> shape;
  TypedArray(uz N) {
    shape.push_back(N);
    values.resize(N);
  }

  Array() {}
  ~Array() {}

  static constexpr TypeType extra_annot = TypedArrayAnnot<T>::value;

  inline TypeType t() const override {
    return TypeType{t_Array} | annot(t_TypedArray) | extra_annot;
  }

  std::ostream &repr(std::ostream &os) const override;
};

inline O<Array> to_untyped(O<Array> arr) {
  // If it's not a typed array, don't do anything!
  if (!arr->t()[t_TypedArray])
    return arr;

  // Else, construct a heterogeneous array with the same shape
  auto* ret = CXBQN_NEW(Array, arr->N());
  ret->shape = arr->shape;

  // For now, just make a new number each time. Might have to revisit chars down
  // the line.
  auto rit = ret->values.begin();
  auto arrit = arr->values.begin();
  while (arrit != arr->values.end())
    *rit = CXBQN_NEW(Number, *arrit++);

  return ret;
}

} // namespace cxbqn::types
