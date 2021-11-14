#pragma once
#include <cxbqn/config.hpp>
#include <cxbqn/fmt.hpp>
#include <string>

#ifdef CXBQN_DEEPCHECKS
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <sstream>
#define CXBQN_DEBUG(...) spdlog::debug(__VA_ARGS__);
#define CXBQN_CRIT(...) spdlog::critical(__VA_ARGS__);
#define CXBQN_INFO(...) spdlog::info(__VA_ARGS__);
#define CXBQN_SETLOGSTR()                                                      \
  do {                                                                         \
    auto l = spdlog::create_async<spdlog::sinks::basic_file_sink_mt>(          \
        "async_file_logger", "cxbqn-debug.log");                               \
    l->set_level(spdlog::CXBQN_LOGLEVEL);                                      \
    l->set_pattern("cxbqn[%^%5l%$]:%v");                                       \
    spdlog::flush_every(std::chrono::seconds(5));                              \
    spdlog::set_default_logger(l);                                             \
  } while (0);
#define CXBQN_LOGFLUSH() spdlog::get("async_file_logger")->flush();
#else
#define CXBQN_DEBUG(...) (void)0
#define CXBQN_CRIT(...) (void)0
#define CXBQN_INFO(...) (void)0
#define CXBQN_DEREF_OR_NULL(x) (void)0
#define CXBQN_SETLOGSTR() (void)0
#define CXBQN_LOGFLUSH() (void)0
#endif

#define CXBQN_STR_NC(x)                                                        \
  static_cast<std::string>((nullptr == x) ? "null" : fmt::format("{}", *x))
#define CXBQN_DEBUG_NC(fmt, x) CXBQN_DEBUG(fmt, CXBQN_STR_NC(x))

#define CXBQN_ATTACH_DEBUGGER_SET_VAR_I_EQ_1_TO_CONTINUE()                     \
  do {                                                                         \
    static bool shouldbreak = false;                                           \
    if (shouldbreak)                                                           \
      break;                                                                   \
    int i = 0;                                                                 \
    const auto pid = getpid();                                                 \
    std::cout << "pid=" << pid << "\n";                                        \
    while (i < 1)                                                              \
      ;                                                                        \
    shouldbreak = true;                                                        \
  } while (0);
