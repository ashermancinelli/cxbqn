#pragma once
#include <cxbqn/config.hpp>
#include <cxbqn/fmt.hpp>

#ifdef CXBQN_DEEPCHECKS
#include <spdlog/spdlog.h>
#include <sstream>
#define CXBQN_DEBUG(...) spdlog::debug(__VA_ARGS__);
#define CXBQN_CRIT(...) spdlog::critical(__VA_ARGS__);
#define CXBQN_INFO(...) spdlog::info(__VA_ARGS__);
#define CXBQN_SETLOGSTR() spdlog::set_pattern("cxbqn[%^%5l%$]:%v");
#else
#define CXBQN_DEBUG(...)
#define CXBQN_CRIT(...)
#define CXBQN_INFO(...)
#define CXBQN_DEREF_OR_NULL(x)
#define CXBQN_SETLOGSTR()
#endif

// Debug a value with a nullcheck
#define CXBQN_DEBUG_NC(fmt, x)                                                 \
  do {                                                                         \
    if (nullptr == x) {                                                        \
      CXBQN_DEBUG(fmt, "null");                                                \
    } else {                                                                   \
      CXBQN_DEBUG(fmt, *x);                                                    \
    }                                                                          \
  } while (0);
