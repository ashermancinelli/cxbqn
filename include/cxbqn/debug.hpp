#pragma once
#include <cxbqn/config.hpp>
#include <cxbqn/fmt.hpp>
#include <string>

#ifdef CXBQN_DEEPCHECKS
#include <spdlog/spdlog.h>
#include <sstream>
#define CXBQN_DEBUG(...) spdlog::debug(__VA_ARGS__);
#define CXBQN_CRIT(...) spdlog::critical(__VA_ARGS__);
#define CXBQN_INFO(...) spdlog::info(__VA_ARGS__);
#define CXBQN_SETLOGSTR()                                                      \
  do {                                                                         \
    spdlog::set_level(spdlog::CXBQN_LOGLEVEL);                                 \
    spdlog::set_pattern("cxbqn[%^%5l%$]:%v");                                  \
  } while (0);
#else
#define CXBQN_DEBUG(...)
#define CXBQN_CRIT(...)
#define CXBQN_INFO(...)
#define CXBQN_DEREF_OR_NULL(x)
#define CXBQN_SETLOGSTR()
#endif

#define CXBQN_STR_NC(x)                                                        \
  static_cast<std::string>((nullptr == x) ? "null" : fmt::format("{}", *x))
#define CXBQN_DEBUG_NC(fmt, x) CXBQN_DEBUG(fmt, CXBQN_STR_NC(x))
