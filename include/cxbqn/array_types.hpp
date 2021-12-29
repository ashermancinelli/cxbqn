#pragma once
#include <cxbqn/config.hpp>
#include <cxbqn/types.hpp>
#include <tuple>
#include <utf8.h>

namespace cxbqn::types {

namespace {

template <typename T> constexpr TypeType typed_array_annot();

template <> constexpr TypeType typed_array_annot<i64>() {
  return annot(t_I64Array);
}
template <> constexpr TypeType typed_array_annot<f64>() {
  return annot(t_F64Array);
}
template <> constexpr TypeType typed_array_annot<uz>() {
  return annot(t_UZArray);
}
template <> constexpr TypeType typed_array_annot<c32>() {
  return annot(t_C32Array);
}

} // namespace

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

  O<Value> get(uz i) const override { return CXBQN_NEW(Number, values[i]); }
  uz N() const override { return values.size(); }
  const std::vector<uz> &shape() const override { return _shape; }
  std::vector<uz> &shape() override { return _shape; }

  O<ArrayBase> copy() const override {
    return CXBQN_NEW(TypedArray<T>, values, _shape);
  }

  inline TypeType t() const override {
    return TypeType{t_Array} | typed_array_annot<T>() | annot(t_TypedArray);
  }

  // Not sure how best to format this. Should probably just rely on •Fmt pulling
  // each value out sequentially.
  std::ostream &repr(std::ostream &os) const override { return os; }
};

template <> struct TypedArray<c32> : public ArrayBase {
  std::u32string values;
  std::vector<uz> _shape;
  TypedArray(const std::u32string &s) : values{s} {
    _shape.push_back(s.size());
  }
  TypedArray(const std::string &s) : values{s.begin(), s.end()} {
    _shape.push_back(s.size());
  }

  O<Value> get(uz i) const override { return CXBQN_NEW(Character, values[i]); }
  uz N() const override { return values.size(); }
  const std::vector<uz> &shape() const override { return _shape; }
  std::vector<uz> &shape() override { return _shape; }
  O<ArrayBase> copy() const override {
    return CXBQN_NEW(TypedArray<c32>, values);
  }

  inline TypeType t() const override {
    return TypeType{t_Array} |
           TypeType{annot(t_String) | annot(t_C32Array) | annot(t_TypedArray)};
  }

  std::ostream &repr(std::ostream &os) const override {
    return os << utf8::utf32to8(values);
  }
};

using String = TypedArray<c32>;

} // namespace cxbqn::types
