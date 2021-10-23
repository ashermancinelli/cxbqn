#pragma once
#include <functional>
#include <scalar_types.hpp>
#include <type_traits>
#include <variant>


namespace cxbqn {

// template deduction guides to make std::visit feel better
template <class... Ts> struct overload : Ts... { using Ts::operator()...; };
template <class... Ts> overload(Ts...) -> overload<Ts...>;

// for nice enum->int casting
template <typename E>
constexpr auto to_underlying(E e) noexcept
{
    return static_cast<std::underlying_type_t<E>>(e);
}

namespace value {

// Using cbqn's enum
enum class Type {
  bit=0,
  i8 =1,
  i16=2,
  i32=3,
  f64=4,
};

struct Value {
  i32 refc;
  Type t;
  union {
    i8  _i8;
    i16 _i16;
    i32 _i32;
    f64 _f64;
  } v;
};

struct Array {
  Value v;
  uz ia;
  uz* sh;
  ~Array() {
    if (sh != nullptr)
      delete[] sh;
  }
};

using Ref = std::shared_ptr<Value>;
using Opt = std::optional<Value>;

auto decode(Ref v) -> Scalar;
auto decode(Root v) -> Scalar;
auto decode(Opt v) -> Scalar;

} // namespace value
} // namespace cxbqn
