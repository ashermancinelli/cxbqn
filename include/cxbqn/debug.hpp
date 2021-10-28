#pragma once
#include <cxbqn/config.hpp>
#include <cxbqn/fmt.hpp>

#ifdef CXBQN_DEEPCHECKS
#include <spdlog/spdlog.h>
#include <sstream>
#define CXBQN_DEBUG(...) spdlog::debug(__VA_ARGS__);
#define CXBQN_CRIT(...) spdlog::critical(__VA_ARGS__);
#else
#define CXBQN_DEBUG(...)
#define CXBQN_CRIT(...)
#endif

namespace cxbqn::debug {

template <typename ValueContainer>
void vdbg(const char *label, ValueContainer c) {
#ifdef CXBQN_DEEPCHECKS
  using namespace cxbqn::fmt;
  std::stringstream ss;
  ss << label << ":[";
  for (const auto e : c) {
    if (nullptr == e)
      ss << "null,";
    else {
      fmt::repr(ss, e);
      ss << ",";
    }
  }
  ss << "]";
  spdlog::debug("{}", ss.str());
#endif
}

template <typename ValueContainer>
void dbg(const char *label, ValueContainer c) {
#ifdef CXBQN_DEEPCHECKS
  using namespace cxbqn::fmt;
  std::stringstream ss;
  ss << label << ":[";
  for (const auto e : c) {
    ss << e << ",";
  }
  ss << "]";
  spdlog::debug("{}", ss.str());
#endif
}

void scope(types::Scope *sc);

} // namespace cxbqn::debug
