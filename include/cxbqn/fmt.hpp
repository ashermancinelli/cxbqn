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
  os << "Block{type=" << static_cast<int>(b.type) << ",imm=" << b.immediate
     << ",varc=" << b.var_count << ",bc=[";
  for (const auto &e : b.bc)
    os << e << ",";
  os << "]}";
  return os;
}

template <> struct fmt::formatter<ByteCodeRef> {
  constexpr auto parse(format_parse_context &ctx) -> decltype(ctx.begin()) {
    return ctx.end();
  }
  template <typename FormatContext>
  auto format(const ByteCodeRef bc, FormatContext &ctx) -> decltype(ctx.out()) {
    std::stringstream ss;
    ss << "[";
    for (const auto &e : bc)
      ss << e << ",";
    ss << "]";
    return format_to(ctx.out(), "{}", ss.str());
  }
};

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
    std::stringstream ss;
    ss << "Scope{parent=" << (s.parent ? "Scope{}" : "nullptr")
       << ",vars.size=" << s.vars.size() << "}";
    return format_to(ctx.out(), "{}", ss.str());
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
#define FMT_VALUE_CONTAINER(Container)                                         \
  template <> struct fmt::formatter<Container<Value *>> {                      \
    constexpr auto parse(format_parse_context &ctx) -> decltype(ctx.begin()) { \
      return ctx.end();                                                        \
    }                                                                          \
    template <typename FormatContext>                                          \
    auto format(const Container<Value *> &vs, FormatContext &ctx)              \
        -> decltype(ctx.out()) {                                               \
      auto &&out = ctx.out();                                                  \
      format_to(out, "{}", "[");                                               \
      for (const auto &v : vs) {                                               \
        if (nullptr == v)                                                      \
          format_to(out, "{}", "null");                                        \
        else                                                                   \
          format_to(out, "{}", *v);                                            \
        format_to(out, "{}", ",");                                             \
      }                                                                        \
      return format_to(out, "{}", "]");                                        \
    }                                                                          \
  };

FMT_VALUE_CONTAINER(std::vector);
FMT_VALUE_CONTAINER(std::deque);

#undef FMT_VALUE_CONTAINER
#undef FORMAT_TO_OR_NULL

template <> struct fmt::formatter<Body> {
  constexpr auto parse(format_parse_context &ctx) -> decltype(ctx.begin()) {
    return ctx.end();
  }
  template <typename FormatContext>
  auto format(const Body &b, FormatContext &ctx) -> decltype(ctx.out()) {
    return format_to(ctx.out(), "Body{nvars={},offset={}}", b.var_count,
                     b.bc_offset);
  }
};

template <>
struct fmt::formatter<std::span<Block>> {
  constexpr auto parse(format_parse_context &ctx) -> decltype(ctx.begin()) {
    return ctx.end();
  }
  template <typename FormatContext>
  auto format(const std::span<Block> &blks, FormatContext &ctx)
      -> decltype(ctx.out()) {
    std::stringstream ss;
    for (const auto &e : blks)
      ss << e << ",";
    return format_to(ctx.out(), "{}", ss.str());
  }
};
