#pragma once
#include <functional>
#include <type_traits>
#include <variant>
#include <scalar_types.hpp>

namespace cxbqn {

// template deduction guides to make std::visit feel better
template <class... Ts> struct overload : Ts... { using Ts::operator()...; };
template <class... Ts> overload(Ts...) -> overload<Ts...>;

namespace value {

// clang-format off
using Scalar = f64;
struct BlockInst { };
struct Array { };
struct Function { };
struct Train2 { };
struct Train3 { };

using Root = std::variant<
  Scalar,
  BlockInst,
  Array,
  Function,
  Train2,
  Train3
>;

using Ref = std::shared_ptr<Root>;
using Opt = std::optional<Ref>;

// clang-format on

auto decode(Ref v) -> Scalar;
auto decode(Root v) -> Scalar;
auto decode(Opt v) -> Scalar;

} // namespace value
} // namespace cxbqn

