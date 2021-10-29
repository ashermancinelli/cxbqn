#pragma once
#include <cxbqn/types.hpp>
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

template <typename OS> OS &operator<<(OS &os, const Block &b) {
  os << "Block{type={" << static_cast<int>(b.type) << "},imm={" << b.immediate
     << "},varc={" << b.var_count << "},bc=[";
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
    return format_to(ctx.out(), "{}", bc);
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
       << ",vars.size=" << s.vars.size()
       << "}";
    return format_to(ctx.out(), "{}", ss.str());
  }
};

template <> struct fmt::formatter<std::span<Block>> {
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
