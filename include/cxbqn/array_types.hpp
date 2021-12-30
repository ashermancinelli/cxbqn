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
  TypedArray(uz N) {
    shape.push_back(N);
    values.resize(N);
  }
  TypedArray(std::vector<T> vals, std::vector<uz> shape)
      : values{vals}, ArrayBase(shape) {}
  TypedArray(std::vector<T> vals) : values{vals} {
    shape.push_back(vals.size());
  }

  O<Value> get(uz i) const override { return CXBQN_NEW(Number, values[i]); }
  uz N() const override { return values.size(); }

  O<ArrayBase> copy() const override {
    return CXBQN_NEW(TypedArray<T>, values, shape);
  }

  inline TypeType t() const override {
    return TypeType{t_Array} | typed_array_annot<T>() | annot(t_TypedArray);
  }

  // Not sure how best to format this. Should probably just rely on •Fmt pulling
  // each value out sequentially.
  std::ostream &repr(std::ostream &os) const override {
    os << "⟨sh=⟨";
    int i=0;
    while (i < shape.size()) {
      os << shape[i];
      if (++i != shape.size())
        os << ",";
    }
    os << "⟩";
    i=0;
    while (i < values.size()) {
      os << values[i];
      if (++i!=values.size())
        os << ",";
    }
    os << "⟩";
    return os; 
  }
};

template <> struct TypedArray<c32> : public ArrayBase {
  std::u32string values;
  TypedArray(const std::u32string &s) : values{s} {
    shape.push_back(s.size());
  }
  TypedArray(const std::string &s) {
    values = utf8::utf8to32(s);
    shape.push_back(values.size());
  }

  O<Value> get(uz i) const override { return CXBQN_NEW(Character, values[i]); }
  uz N() const override { return values.size(); }
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
