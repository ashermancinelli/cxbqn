#pragma once
#include <cxbqn/types.hpp>
#include <deque>
#include <iostream>
#include <spdlog/fmt/bundled/format.h>
#include <spdlog/spdlog.h>
#include <sstream>

using namespace cxbqn::types;

template <typename OS> OS &operator<<(OS &os, const ByteCodeRef &bc) {
  os << "[";
  for (const auto &e : bc)
    os << e << ",";
  os << "]";
  return os;
}

template <typename OS> OS &operator<<(OS &os, const Value *v) {
  return v->repr(os);
}

template <typename OS> OS &operator<<(OS &os, const Block &b) {
  os << "(block type=" << static_cast<int>(b.def.type)
     << " imm=" << b.def.immediate << " ";
  if (b.def.immediate) {
    auto [bc, nvars] = b.body();
    os << "nvars=" << nvars << " ";
  } else {
    if (b.def.mon_body_idxs.size()) {
      auto [bc, nvars] = b.body(1);
      os << "nvars1=" << nvars << " ";
    }
    if (b.def.dya_body_idxs.size()) {
      auto [bc, nvars] = b.body(2);
      os << "nvars2=" << nvars << " ";
    }
  }
  os << ")";
  return os;
}

template <> struct fmt::formatter<Block> {
  constexpr auto parse(format_parse_context &ctx) -> decltype(ctx.begin()) {
    return ctx.end();
  }
  template <typename FormatContext>
  auto format(const Block &b, FormatContext &ctx) -> decltype(ctx.out()) {
    std::stringstream ss;
    ss << b;
    return format_to(ctx.out(), "{}", ss.str());
  }
};

template <> struct fmt::formatter<Scope> {
  constexpr auto parse(format_parse_context &ctx) -> decltype(ctx.begin()) {
    return ctx.end();
  }
  template <typename FormatContext>
  auto format(const Scope &s, FormatContext &ctx) -> decltype(ctx.out()) {
    auto &&out = ctx.out();
    format_to(out, "(scp p={},v={})", (s.parent ? "scp" : "null"), s.vars);
    return out;
  }
};

template <> struct fmt::formatter<Character> {
  constexpr auto parse(format_parse_context &ctx) -> decltype(ctx.begin()) {
    return ctx.end();
  }
  template <typename FormatContext>
  auto format(Character const &v, FormatContext &ctx) -> decltype(ctx.out()) {
    auto &&out = ctx.out();
    format_to(out, L"{}", (char32_t)v.c());
    return out;
  }
};

template <> struct fmt::formatter<Array> {
  constexpr auto parse(format_parse_context &ctx) -> decltype(ctx.begin()) {
    return ctx.end();
  }
  template <typename FormatContext>
  auto format(Array const &v, FormatContext &ctx) -> decltype(ctx.out()) {
    auto &&out = ctx.out();
    if (v.t()[t_String]) {
      for (const auto* e : v.values)
        format_to(out, L"{}", std::string(dynamic_cast<Character*>(e)->c()));
      return out;
    }
    format_to(out, "{}", v);
    return out;
  }
};

template <> struct fmt::formatter<Value> {
  constexpr auto parse(format_parse_context &ctx) -> decltype(ctx.begin()) {
    return ctx.end();
  }
  template <typename FormatContext>
  auto format(Value const &v, FormatContext &ctx) -> decltype(ctx.out()) {
    std::stringstream ss;
    v.repr(ss);
    return format_to(ctx.out(), "{}", ss.str());
  }
};

#define FORMAT_TO_OR_NULL(out, str, x)                                         \
  if (nullptr == (x))                                                          \
    format_to(out, str, "null");                                               \
  else                                                                         \
    format_to(out, str, *x);

// These require a null check first - the rest can be built from a template
// macro
#define FMT_PTR_CONTAINER(Container, ValueType)                                \
  template <> struct fmt::formatter<Container<ValueType *>> {                  \
    constexpr auto parse(format_parse_context &ctx) -> decltype(ctx.begin()) { \
      return ctx.end();                                                        \
    }                                                                          \
    template <typename FormatContext>                                          \
    auto format(const Container<ValueType *> &vs, FormatContext &ctx)          \
        -> decltype(ctx.out()) {                                               \
      auto &&out = ctx.out();                                                  \
      std::vector<ValueType *> vvs(vs.begin(), vs.end());                      \
      format_to(out, "{}", "⟨");                                               \
      for (int i = 0; i < vvs.size(); i++) {                                   \
        if (nullptr == vvs[i])                                                 \
          format_to(out, "{}", "null");                                        \
        else                                                                   \
          format_to(out, "{}", *vvs[i]);                                       \
        if (i + 1 < vvs.size())                                                \
          format_to(out, "{}", ",");                                           \
      }                                                                        \
      return format_to(out, "{}", "⟩");                                        \
    }                                                                          \
  }; \
  template <> struct fmt::formatter<Container<O<ValueType>>> {                  \
    constexpr auto parse(format_parse_context &ctx) -> decltype(ctx.begin()) { \
      return ctx.end();                                                        \
    }                                                                          \
    template <typename FormatContext>                                          \
    auto format(const Container<O<ValueType>> &vs, FormatContext &ctx)          \
        -> decltype(ctx.out()) {                                               \
      auto &&out = ctx.out();                                                  \
      std::vector<O<ValueType>> vvs(vs.begin(), vs.end());                      \
      format_to(out, "{}", "⟨");                                               \
      for (int i = 0; i < vvs.size(); i++) {                                   \
        if (nullptr == vvs[i])                                                 \
          format_to(out, "{}", "null");                                        \
        else                                                                   \
          format_to(out, "{}", *vvs[i]);                                       \
        if (i + 1 < vvs.size())                                                \
          format_to(out, "{}", ",");                                           \
      }                                                                        \
      return format_to(out, "{}", "⟩");                                        \
    }                                                                          \
  };


FMT_PTR_CONTAINER(std::vector, Value);
FMT_PTR_CONTAINER(std::deque, Value);
FMT_PTR_CONTAINER(std::span, Value);
FMT_PTR_CONTAINER(std::initializer_list, Value);

#undef FMT_PTR_CONTAINER
#undef FORMAT_TO_OR_NULL

template <> struct fmt::formatter<Body> {
  constexpr auto parse(format_parse_context &ctx) -> decltype(ctx.begin()) {
    return ctx.end();
  }
  template <typename FormatContext>
  auto format(const Body &b, FormatContext &ctx) -> decltype(ctx.out()) {
    return format_to(ctx.out(), "Body<nvars={},offset={}>", b.var_count,
                     b.bc_offset);
  }
};

/*
 * \pre you can foreach over the container
 * \pre each element is `format_to`-able
 */
#define FMT_VALUE_CONTAINER(Container)                                         \
  template <> struct fmt::formatter<Container> {                               \
    constexpr auto parse(format_parse_context &ctx) -> decltype(ctx.begin()) { \
      return ctx.end();                                                        \
    }                                                                          \
    template <typename FormatContext>                                          \
    auto format(const Container &vs, FormatContext &ctx)                       \
        -> decltype(ctx.out()) {                                               \
      auto &&out = ctx.out();                                                  \
      format_to(out, "{}", "⟨");                                               \
      for (const auto &e : vs)                                                 \
        format_to(out, "{},", e);                                              \
      return format_to(out, "{}", "⟩");                                        \
    }                                                                          \
  };

FMT_VALUE_CONTAINER(std::span<Block>);
FMT_VALUE_CONTAINER(std::vector<cxbqn::uz>);
FMT_VALUE_CONTAINER(std::vector<std::vector<cxbqn::uz>>);
FMT_VALUE_CONTAINER(std::span<cxbqn::uz>);
FMT_VALUE_CONTAINER(ByteCodeRef);

#undef FMT_VALUE_CONTAINER
