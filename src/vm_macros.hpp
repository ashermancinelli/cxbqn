#pragma once
#include <cxbqn/debug.hpp>
#include <map>
#include <spdlog/fmt/bundled/color.h>
#include <string>

namespace cxbqn {

#ifdef CXBQN_PROFILE_VM
static std::map<std::string, uz> instr_counts;
#define INCR_INSTR(x) instr_counts[x]++;
#define INSTR_REPORT()                                                         \
  do {                                                                         \
    const auto tot =                                                           \
        std::accumulate(instr_counts.begin(), instr_counts.end(), 0,           \
                        [](auto acc, auto kv) { return acc + kv.second; });    \
    std::vector<std::pair<std::string, uz>> freq;                              \
    for (const auto it : instr_counts)                                         \
      freq.push_back(it);                                                      \
    std::sort(freq.begin(), freq.end(),                                        \
              [](auto a, auto b) { return a.second > b.second; });             \
    fmt::print("{:^30}{:<20}{:<20}\n", "instruction", "count", "\% of total"); \
    for (const auto &[k, v] : freq) {                                          \
      fmt::print("{:^30}{:<20}{:<2.5f}\n", k, v, 100.0 * ((f64)v / tot));      \
    }                                                                          \
  } while (0);
#else
#define INCR_INSTR(...)
#define INSTR_REPORT()
#endif

#ifdef CXBQN_DEBUG_VM

#ifdef CXBQN_COLOR
#define INSTR_CL (fmt::fg(fmt::color::cyan)),
#define PC_CL (fmt::fg(fmt::color::light_green)),
#define ARG_CL (fmt::fg(fmt::color::yellow)),
#define EVAL_CL (fmt::fg(fmt::color::orange)),
#define STK_CL (fmt::fg(fmt::color::light_coral)),
#else
#define INSTR_CL
#define PC_CL
#define ARG_CL
#define EVAL_CL
#define STK_CL
#endif

// Print the program counter
#define INSTR_PC(pc) fmt::print(PC_CL "@{:<4}", pc)

// Print the instruction
#define INSTR_INSTR(x) fmt::print(INSTR_CL "{}", x)

// Print the stack
#define P_STK()                                                                \
  do {                                                                         \
    std::stringstream ss;                                                      \
    for (int i = 0; i < stk.size(); i++) {                                     \
      ss << CXBQN_STR_NC(stk[i]);                                              \
      if (i + 1 < stk.size())                                                  \
        ss << "; ";                                                            \
    }                                                                          \
    fmt::print(STK_CL "  {}", ss.str());                                       \
  } while (0);

// Indent according to the level of nesting in the given vm execution
static cxbqn::u8 indent = -1;
#define INDENT()                                                               \
  for (int i = 0; i < indent; i++)                                             \
    fmt::print("    ");

#define INSTR(x)                                                               \
  do {                                                                         \
    INCR_INSTR(x);                                                             \
    INSTR_PC(pc);                                                              \
    INDENT();                                                                  \
    INSTR_INSTR(x);                                                            \
    fmt::print("{:<6}", ""); \
    P_STK();                                                                   \
    fmt::print("\n");                                                          \
  } while (0);
#define INSTR1(x)                                                              \
  do {                                                                         \
    INCR_INSTR(x);                                                             \
    INSTR_PC(pc);                                                              \
    INDENT();                                                                  \
    INSTR_INSTR(x);                                                            \
    const auto s = fmt::format(" {}", bc[pc + 1]);                             \
    fmt::print(ARG_CL "{:<6}", s);                                             \
    P_STK();                                                                   \
    fmt::print("\n");                                                          \
  } while (0);
#define INSTR2(x)                                                              \
  do {                                                                         \
    INCR_INSTR(x);                                                             \
    INSTR_PC(pc);                                                              \
    INDENT();                                                                  \
    INSTR_INSTR(x);                                                            \
    const auto s = fmt::format(" {} {}", bc[pc + 1], bc[pc + 2]);              \
    fmt::print(ARG_CL "{:<6}", s);                                             \
    P_STK();                                                                   \
    fmt::print("\n");                                                          \
  } while (0);

#define CXBQN_NEWEVAL()                                                        \
  do {                                                                         \
    indent++;                                                                  \
    INDENT();                                                                  \
    fmt::print(EVAL_CL "     {}\n", "new eval");                               \
  } while (0);

#define CXBQN_ENDEVAL()                                                        \
  do {                                                                         \
    INDENT();                                                                  \
    fmt::print(EVAL_CL "     {}\n", "end eval");                               \
    indent--;                                                                  \
  } while (0);

#else
#define CXBQN_NEWEVAL(...)
#define CXBQN_ENDEVAL(...)
#define INSTR(...)
#define INSTR1(...)
#define INSTR2(...)
#endif

} // namespace cxbqn
